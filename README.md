# qxLib

| Compiler | Debug | Release |
| :---: | :---: | :---: |
| Clang 11.0.1 | ![ubuntu_clang_debug](https://github.com/n0lavar/qxLib/workflows/ubuntu_clang_debug/badge.svg)  | ![ubuntu_clang_release](https://github.com/n0lavar/qxLib/workflows/ubuntu_clang_release/badge.svg)  |
| GCC 10.1 | ![ubuntu_gcc_debug](https://github.com/n0lavar/qxLib/workflows/ubuntu_gcc_debug/badge.svg)  | ![ubuntu_gcc_release](https://github.com/n0lavar/qxLib/workflows/ubuntu_gcc_release/badge.svg)  |
| MSVC 19.28 | ![windows_msvc_debug](https://github.com/n0lavar/qxLib/workflows/windows_msvc_debug/badge.svg) | ![windows_msvc_release](https://github.com/n0lavar/qxLib/workflows/windows_msvc_release/badge.svg) |
| Apple Clang 12.0 | ![macos_clang_debug](https://github.com/n0lavar/qxLib/workflows/macos_clang_debug/badge.svg) | ![macos_clang_release](https://github.com/n0lavar/qxLib/workflows/macos_clang_release/badge.svg) |

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ab3175ce6af6453284f8a639306a6935)](https://www.codacy.com/manual/n0lavar/qxLib?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=n0lavar/qxLib&amp;utm_campaign=Badge_Grade)[![codecov](https://codecov.io/gh/n0lavar/qxLib/branch/master/graph/badge.svg)](https://codecov.io/gh/n0lavar/qxLib)

A few useful things for developing your own game engine with OpenGL:
+ RAII for OpenGL stuff:
  + ebo
  + fbo
  + rbo
  + shader_program
  + shader_vert, shader_tesc, shader_tese, shader_geom, shader_frag, shader_comp
  + ssbo
  + texture
  + ubo
  + vao
+ containers:
  + string with extended interface (format, apply_case, to\<T\>, from\<T\>, trim_left, trim_right, trim, remove, remove_prefix, remove_suffix, remove_all, replace, replace_all, split, contains)
  + vector2d class of cache friendly two dimentional vector
  + triangular_vector class where only elements with nRow >= nCols are stored
+ constexpr classes:
  + constexpr_flag (returns "Start" at the beginning(test), "Start" with test_and_set and "End" after)
  + constexpr_sequence (returns new value with each "next()" calling depending on given "Func")
  + constexpr_funcs (some std algorithms with constexpr qualifier)
  + constexpr_random (returns new pseudorandom value with each "next()" calling)
+ thread_worker
+ asserts
  + QX_DEBUG_BREAK (breaks debugging)
  + QX_ASSERT (breaks debugging depending on condition)
  + QX_ASSERT_MSG (breaks debugging depending on condition with specific message)
+ logger
  + registering units: function, method, file or tag
  + enabling and disabling logging to file for each unit
  + enabling and disabling logging to console for each unit
  + setting formatting function for each unit
  + colored output to console
  + logger_singleton and macros for plug and play
+ logger_worker (thread safe logger)
+ rtti (realization based on virtual functions, can be used without rtti compiler flag)
+ singleton (Meyer's singleton macro)
+ smart_enum: (declare once and convert enum and string into each other)
+ type_traits:
  + is_iterator_v
  + is_random_access_iterator_v
  + are_same_v (check if all of variadic arguments are same type)
  + iterator_value_t
  + is_specialization_exist_v (decide if a struct/class specialization exist)
  + is_specialization_of
+ useful_macros:
  + QX_STRINGIFY (turn any text in your code into a string)
  + QX_LINE_NAME (creates a unique name using the line number)
  + QX_SHORT_FILE (cuts full absolute path to the file name only : C:\folder1\foler2\file.cpp  =>  file.cpp)
  + QX_SINGLE_ARGUMENT (let macro param containing commas work fine)
  + etc
+ some algorithms implementations:
  + linear_interpolation
  + bilinear_inletpolation
  + integrate_rectangle_rule
  + integrate_trapezoid_rule
  + integrate_adaptive_midpoint
  + integrate_monte_carlo
  + find_zero_newtons_method
  + gcd
  + lcm
  + pow for integer power with highly improved performance versus std::pow
  + maxpot (max power of two in integer)
  + find_prime_factors
  + find_primes
  + is_prime
+ sorting algorithms:
  + sort_insertion
  + sort_selection
  + sort_bubble
  + sort_heap
  + sort_quick_hoare
  + sort_quick_three_way
  + sort_quick_dual_pivot
  + sort_merge
  + sort_counting

Dependencies:
+ C++17
+ glm for gl module and some algorithms
+ glew if you want to use gl module
  
## License

qxLib is available under the GNU General Public License v3.0. See LICENSE.txt.


## Authors

qxLib was mainly written and is maintained by Nick Khrapov
(nick.khrapov@gmail.com). See the git commit log for other authors.
