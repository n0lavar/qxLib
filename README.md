# qxLib
[![Donate](https://img.shields.io/badge/Donate-8A2BE2)](https://revolut.me/n0lavar)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ab3175ce6af6453284f8a639306a6935)](https://www.codacy.com/manual/n0lavar/qxLib?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=n0lavar/qxLib&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/n0lavar/qxLib/branch/master/graph/badge.svg)](https://codecov.io/gh/n0lavar/qxLib)
[![licence](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/n0lavar/qxLib/blob/master/LICENSE)

The library contains various classes, functions and macros that can be useful when developing games and game engines.  
The code is designed to be as performant, extensible and generic as possible. It follows the style of the standard library in terms of code style, use of iterators, traits, etc. The library is intended to extend the functionality of the standard library and not copy it.

Some examples:
* Implementations of observer, singleton, generic iterator, double dispatch and other patterns;
* A string that fully follows the std::string interface and supports compile-time configuration of a large number of parameters (SSO size, alignment, hashing algorithms, comparison, formatting, etc.) and contains additional methods (`format(), to_lower()/to_upper(), to<T>(), from<T>(), trim()/trim_right()/trim_left(), remove_prefix()/remove_suffix(), split()` etc.);
* Extension of standard library algorithms;
* Macro based RTTI system;
* Additional containers, e.g. cache friendly 2d vector, pool of unique objects, symmetric matrix container , etc.;
* Easing algorithms for working with animation;
* Streams based logging system;

...and much more. See [doxygen documentation](https://n0lavar.github.io/qxLib/files.html) for more info.

Feel free to suggest any improvements.

## Status:

| Compiler<br />(uses the last machine,<br />see logs for a compiler version) | Debug | Release |
| :---: | :---: | :---: |
| Clang | ![ubuntu_clang_debug](https://github.com/n0lavar/qxLib/workflows/ubuntu_clang_debug/badge.svg)  | ![ubuntu_clang_release](https://github.com/n0lavar/qxLib/workflows/ubuntu_clang_release/badge.svg)  |
| GCC | ![ubuntu_gcc_debug](https://github.com/n0lavar/qxLib/workflows/ubuntu_gcc_debug/badge.svg)  | ![ubuntu_gcc_release](https://github.com/n0lavar/qxLib/workflows/ubuntu_gcc_release/badge.svg)  |
| MSVC | ![windows_msvc_debug](https://github.com/n0lavar/qxLib/workflows/windows_msvc_debug/badge.svg) | ![windows_msvc_release](https://github.com/n0lavar/qxLib/workflows/windows_msvc_release/badge.svg) |
| Apple Clang | ![macos_clang_debug](https://github.com/n0lavar/qxLib/workflows/macos_clang_debug/badge.svg) | ![macos_clang_release](https://github.com/n0lavar/qxLib/workflows/macos_clang_release/badge.svg) |

## Dependencies:

Required:
+ C++20

Optional:
+ glm (/gl, /render, /math)
+ boost (qx::unique_objects_pool)
  
## License

qxLib is available under the MIT License. See LICENSE.txt.


## Authors

qxLib was mainly written and is maintained by Nick Khrapov  
(nick.khrapov@gmail.com). See the git commit log for other authors.
