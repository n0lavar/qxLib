# Documentation rules

- All classes, functions, methods, macros, and files must be properly documented.
- Avoid pointless documentation like `@param color - color`. Describe what this this is for, edge cases (if any), contracts (if any), and so on.

# Documentation style

- Use multiline documentation comments with `/**` and `**/` on separate lines. Single-line comments such as `/** @brief List all registered variables, sorted by runtime name. **/` are not allowed.
- `@brief` and `@details` are aligned.
- `@tparam`, `@param` and `@return` are aligned and have ` - ` (the `-` character must be indented the same distance from the beginning of the line for all elements). If possible, they also should be aligned with `@brief` and `@details`.
- Like any cpp code, the width is limited by 120 symbols.
- `@return` must be used, never `@retval`.

## File documentation

Place the documentation at the beginning of the file, before `#pragma once` or includes. Include `@file`, `@author`, `@date`, and `@copyright`, aligned as shown below. Use `DD.MM.YYYY` for dates (a single-digit day is also used in existing files). Keep a blank line after `/**` and before `**/`. File-level `@brief` and `@details` may be added when needed.

For a new file, use its actual name, author, creation date, and copyright information.

```cpp
/**

    @file      error_context.h
    @author    Khrapov
    @date      10.02.2026
    @copyright (c) Nick Khrapov, 2026. All right reserved.

**/
#pragma once
```

## Class documentation

Include `@class`, `@brief`, `@author`, and `@date`. Describe relevant contracts with `@details` and every template parameter with `@tparam`. Keep a blank line after `/**` and before `**/`, as in file documentation. Use the class name and template parameter names from the project's code style.

Documentation may be omitted (but is not prohibited) for the following elements:

- Structures (assumed to be simple enough to describe through their names).
- Specializations of helper structures (`std::hash`, `std::formatter`, etc.).

```cpp
/**

    @class   moving_average
    @brief   Calculates a moving average over the most recent entries.
    @tparam  T - floating point type
    @author  Khrapov
    @date    1.06.2021

**/
template<class T>
class moving_average;
```

## Macro documentation

Describe the macro's purpose and every parameter, including variadic arguments, with `@param`. Describe the result with `@return` if the macro produces a value. Document evaluation count and side effects when relevant. Macro comments do not need the extra blank lines used in file and class comments.

```cpp
/**
    @brief   Evaluates an expression and discards its result.
    @details The expression is evaluated exactly once; its side effects are preserved.
    @param   value - expression to evaluate
**/
#define QX_DISCARD(value) static_cast<void>(value)
```

## Function documentation

Function and method documentation must describe every template parameter declared by the function or method with `@tparam`, every function parameter with `@param`, and the result with `@return`. For `void` functions, constructors, and destructors, there is no result to document. The exceptions below still apply.

Describe relevant constraints and edge cases. Function comments do not need the extra blank lines used in file and class comments.

Documentation may be omitted (but is not prohibited) for the following elements:

- Constructors and `init`/`Init` methods without arguments.
- Destructors.
- Any methods using `= default`.
- Operators, if they do exactly what first comes to mind and have no side effects.
- Overridden virtual functions (do not duplicate the description from the base class). Instead, group these methods by base class and add the following before the group:

    ```
    // base_class
    //
    virtual void foo() override;
    virtual void bar() override;
    ```

- Functions in namespace `Details`/`details`.
- Specializations of helper functions.
- Builder return values (`*this`).
- private methods
- static functions in cpp

```cpp
/**
    @brief   Restricts a value to the specified inclusive range.
    @details The lower bound must not exceed the upper bound.
    @tparam  value_t - value type supporting comparison and copying
    @param   value   - value to restrict
    @param   min     - inclusive lower bound
    @param   max     - inclusive upper bound
    @return          - min if value is below min, max if value is above max, otherwise value
**/
template<class value_t>
value_t clamp(value_t value, value_t min, value_t max);
```
