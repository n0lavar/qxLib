#!/usr/bin/env python3
"""Pre-commit fix-up: staged text files are re-saved as UTF-8.

Project convention: all sources are UTF-8 without BOM (see .editorconfig).
The hook converts staged content from whatever encoding it is in:

* UTF-16/32 (LE/BE) with a BOM and UTF-8 with a BOM are detected exactly;
* BOM-less 8-bit text cannot be detected exactly with the standard library
  only, so the first legacy candidate that decodes cleanly into plausible
  text (no control characters) wins. The list is ordered by the repository
  history (CP1251 first) and can be extended in LEGACY_ENCODINGS;
* files that are neither UTF-8 nor any candidate encoding abort the commit
  (silently committing undecodable bytes is worse than a failed commit).

The index entry is replaced and, when the working copy matches the index,
it is updated too; the commit proceeds. One line is logged for every file
that was actually changed; conforming files produce no output. .rc files
get/keep a UTF-8 BOM because rc.exe requires it.

This is the single implementation, kept in the git-hooks/scripts subfolder
so that it follows the regular project CRLF rule; the repository hooks
(pre-commit stubs) invoke this script. qxEngine/qxGame resolve it via the
sibling qxLib checkout, which can be overridden with the QX_LIB_FOLDER
environment variable.
"""

import logging
import subprocess
import sys
import unicodedata
from codecs import BOM_UTF8, BOM_UTF16_BE, BOM_UTF16_LE, BOM_UTF32_BE, BOM_UTF32_LE
from pathlib import Path

logger = logging.getLogger(__name__)

# BOM-less 8-bit encodings, tried in order; the first clean, plausible decode
# wins. The repository history is Russian CP1251, so it comes first. Extend
# the list if sources in other legacy encodings ever appear.
LEGACY_ENCODINGS = ("cp1251", "cp1252", "cp1250", "koi8_r", "cp866", "iso8859_5")


def staged_paths():
    """Return the paths of staged added/copied/modified/renamed files."""
    out = subprocess.run(
        ["git", "diff", "--cached", "--name-only", "--diff-filter=ACMR", "-z"],
        capture_output=True, check=True,
    ).stdout
    return [p.decode("utf-8", "surrogateescape") for p in out.split(b"\0") if p]


def staged_blob(path):
    """Return the staged content of a file, or None when it has no blob."""
    proc = subprocess.run(["git", "cat-file", "blob", f":{path}"], capture_output=True)
    return proc.stdout if proc.returncode == 0 else None


def staged_mode(path):
    """Return the index mode of a file, or None when it has no normal stage."""
    out = subprocess.run(["git", "ls-files", "-s", "--", path], capture_output=True, check=True).stdout
    for line in out.splitlines():
        meta = line.split(b"\t", 1)[0]      # "<mode> <sha> <stage>"
        mode, sha, stage = meta.split()
        if stage == b"0":
            return mode.decode()
    return None


def stage_blob(path, mode, data):
    """Replace the staged blob of a file with the given content."""
    sha = subprocess.run(["git", "hash-object", "-w", "--stdin", f"--path={path}"],
                         input=data, capture_output=True, check=True).stdout.decode().strip()
    subprocess.run(["git", "update-index", "--cacheinfo", mode, sha, path], check=True)


def decode_legacy(body):
    """Decode BOM-less 8-bit bytes with the first fitting candidate encoding."""
    for enc in LEGACY_ENCODINGS:
        try:
            text = body.decode(enc)
        except UnicodeDecodeError:
            continue
        if any(unicodedata.category(c) == "Cc" and c not in "\t\n\r\f" for c in text):
            continue        # control characters: this is not that code page
        return text, enc.upper()
    return None, None


def fixed_content(data, path):
    """Return (new, reason) to re-save, (None, reason) when not convertible,
    or (None, None) when the content already conforms."""
    is_rc = path.lower().endswith(".rc")

    def to_utf8(text):
        new = text.encode("utf-8")
        return BOM_UTF8 + new if is_rc else new     # .rc keeps a BOM for rc.exe

    # BOM-tagged UTF-16/32 first: their bytes contain NULs and would look
    # binary, and UTF-32 LE starts with the UTF-16 LE BOM.
    for bom, label, codec in ((BOM_UTF32_LE, "UTF-32 LE", "utf-32-le"),
                              (BOM_UTF32_BE, "UTF-32 BE", "utf-32-be"),
                              (BOM_UTF16_LE, "UTF-16 LE", "utf-16-le"),
                              (BOM_UTF16_BE, "UTF-16 BE", "utf-16-be")):
        if data.startswith(bom):
            try:
                text = data[len(bom):].decode(codec)
            except UnicodeDecodeError:
                return None, f"{label} payload is not valid {label}"
            return to_utf8(text), f"{label} -> UTF-8"

    if b"\x00" in data:
        return None, None                           # binary, encoding does not apply

    body = data[3:] if data.startswith(BOM_UTF8) else data
    try:
        body.decode("utf-8")
    except UnicodeDecodeError:
        text, enc = decode_legacy(body)
        if text is None:
            candidates = ", ".join(enc.upper() for enc in LEGACY_ENCODINGS)
            return None, f"not UTF-8, no legacy encoding fits ({candidates})"
        return to_utf8(text), f"{enc} -> UTF-8"

    if data.startswith(BOM_UTF8) and not is_rc:
        return body, "removed UTF-8 BOM"
    return None, None


def main():
    logging.basicConfig(level=logging.INFO, stream=sys.stderr, format="pre-commit: %(message)s")

    failed = []
    for path in staged_paths():
        blob = staged_blob(path)
        if blob is None:
            continue          # not present in the index (deleted)
        new, reason = fixed_content(blob, path)
        if new is None and reason is None:
            continue          # already conforming or binary
        if new is None:
            failed.append((path, reason))
            continue
        mode = staged_mode(path)
        if mode is None:
            failed.append((path, "unmerged index entry"))
            continue
        stage_blob(path, mode, new)
        try:
            if Path(path).read_bytes() == blob:
                Path(path).write_bytes(new)   # keep the working copy in sync
        except OSError:
            pass
        logger.info(f"reformatted ({reason}): {path}")

    if failed:
        details = "\n".join(f"    {path} ({reason})" for path, reason in failed)
        logger.error(
            "ERROR, staged files cannot be converted:\n"
            f"{details}\n\n"
            "Re-save them as UTF-8 without BOM (Rider: File Properties > Encoding > UTF-8,\n"
            "choose 'Convert'), and commit again; if the encoding is legitimate, add it\n"
            "to LEGACY_ENCODINGS in tools/git-hooks/scripts/reformat_utf8.py."
        )
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
