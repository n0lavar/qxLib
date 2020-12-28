# qxLib

| Compiler | Debug | Release |
| :---: | :---: | :---: |
| Clang 11.0.1 | ![ubuntu_clang_debug](https://github.com/n0lavar/qxLib/workflows/ubuntu_clang_debug/badge.svg)  | ![ubuntu_clang_release](https://github.com/n0lavar/qxLib/workflows/ubuntu_clang_release/badge.svg)  |
| GCC 10.1 | ![ubuntu_gcc_debug](https://github.com/n0lavar/qxLib/workflows/ubuntu_gcc_debug/badge.svg)  | ![ubuntu_gcc_release](https://github.com/n0lavar/qxLib/workflows/ubuntu_gcc_release/badge.svg)  |
| MSVC 19.28 | ![windows_msvc_debug](https://github.com/n0lavar/qxLib/workflows/windows_msvc_debug/badge.svg) | ![windows_msvc_release](https://github.com/n0lavar/qxLib/workflows/windows_msvc_release/badge.svg) |
| Apple Clang 12.0 | ![macos_clang_debug](https://github.com/n0lavar/qxLib/workflows/macos_clang_debug/badge.svg) | ![macos_clang_release](https://github.com/n0lavar/qxLib/workflows/macos_clang_release/badge.svg) |

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ab3175ce6af6453284f8a639306a6935)](https://www.codacy.com/manual/n0lavar/qxLib?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=n0lavar/qxLib&amp;utm_campaign=Badge_Grade)[![codecov](https://codecov.io/gh/n0lavar/qxLib/branch/master/graph/badge.svg)](https://codecov.io/gh/n0lavar/qxLib)

A few useful things for developing your own game engine with OpenGL:
+ RAII for OpenGL stuff
+ non-standart containers (like triangular vector or vector2d) or more practical containers (like string with "from", "to", "format" etc methods)
+ some algorithms implementations
+ other things like logger(with enabling/disabling logging from particular file or function), smart enum(with "to_string", "from_string" methods), assertions etc

Dependencies:
+ C++17
+ glm for gl module and some algorithms
+ glew if you want to use gl module
  
## License

qxLib is available under the GNU General Public License v3.0. See LICENSE.txt.


## Authors

qxLib was mainly written and is maintained by Nick Khrapov
(nick.khrapov@gmail.com). See the git commit log for other authors.
