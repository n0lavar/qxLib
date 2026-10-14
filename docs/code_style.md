# qxLib code style

The public API follows the standard library style: `snake_case`, iterators, traits, and standard type aliases. Preserve naming and compatibility when changing an existing API.

## Type Naming

| Entity | Example | Comment |
|-|-|-|
| struct | `string_traits`, `config` | Simple data, configuration, traits, and metaprogramming helpers. Methods and inheritance are allowed, as in standard traits. |
| class | `vector2d`, `base_logger_stream` | A type with encapsulated data and logic. |
| enum | `priority`, `verbosity` | Prefer `enum class`. Use `snake_case` for both enum types and enumerators: `priority::very_high`. |
| alias (using) | `value_type`, `size_type`, `delegate_token_type` | Use `using` instead of `typedef`. Preserve standard interface names: `pointer`, `reference`, `iterator`, `const_iterator`, etc. |
| template parameter | `T`, `U`, `char_t`, `traits_t` | Use `class` for type parameters; use `typename` for dependent type names. Use descriptive `snake_case` names ending in `_t`, and names such as `args_t` or `dependencies_t` for packs. |
| concept | `arithmetic_c`, `callable_c`, `range_of_t_c` | Use `snake_case` with the `_c` suffix. |

## Data Naming

### Scope Prefixes

| Type | Example | Comment |
|-|-|-|
| class member | `m_Name` | Any class member. |
| struct member | `bName` | Structure members (which must be public) have no scope prefix. |
| static | `s_Name` | A static class member or a static method in a function or method. |
| global variable | `g_Name` | A variable at file or namespace scope. Should generally be avoided. |
| global constant | `k_Name` | A constexpr or const constant at file, namespace, structure, or class scope. |
| local variable / argument | `bName` | Usually `camelCase` with a type prefix where applicable. Short conventional names (`it`, `i`, `args`) are allowed. |

### Type Prefixes

| Type | Example | Comment |
|-|-|-|
| boolean | bVar | `bool` or a one-bit bitfield. |
| integral | nVar | `short/long/- unsigned/signed int` and any of their aliases (`i8`, `i16`, `i32`, `i64`, `u6`, `u18`, `u32`, `u64`, `size_t`, `std::uint8_t` etc). |
| floating point | fVar | `float`/`double`/`long double` and any of their aliases (`f32`, `f64`, `std::float_t`, `std::double_t`, etc). |
| string | sVar | `qx::string`, `std::string`, and any other string classes. |
| enum | eVar | Scoped and unscoped enums and `qx::flags<>`. |
| chars | chVar | `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t`. |
| string pointer | pszVar | pointer to string, zero terminated. `const/- charType*`.<br>Should be avoided in favor of strings and string views; allowed when interacting with third-party dependencies or legacy code.|
| string view | svVar | `qx::string_view`, `std::string_view`. |
| pointer | pVar | Any const or non-const pointer to an object (except strings; see string pointer). |
| optional | optVar | `std::optional<T>`. The prefix of the contained type is ignored. |

## Rules for Writing Code Entities

### Files

- Move function and method realization to their own files (`.inl`) if realization is larger then interfaces (including documentation and class bodies).

### Classes

- Multiple inheritance is prohibited, except for interfaces.
- The class body is the interface read by the user, so:
    - Members the user will use should appear visually higher. Declare class members in the following order:
        - public methods.
        - protected methods.
        - private methods.
        - protected data.
        - private data.
    - Within each method section, use the following order:
        - Constructors and factory methods.
        - Destructor.
        - Class methods.
        - Virtual method overrides/implementations, grouped by class, starting with the base class and following the order in which interfaces are listed.
    - Class methods must be defined outside the class. This helps readers focus on *what* the class does rather than *how* it does it, and see more of the interface at a glance. Exception: empty implementations, especially in interfaces.
- public variables are prohibited, but static constants may be public.
- protected variables should generally be avoided.
- When overriding methods, their access visibility must be no broader than in the parent class. For example, if `foo` is a `protected` method in the parent class, it may be `protected` or `private` in the current class. If `private` is chosen, a subclass of the current class may only declare its override as `private`.
- Overridden methods must have exactly the same attributes (`[[nodiscard]]`, `[[maybe_unused]]`, etc) and default arguments. Class behavior must not change when the pointer type is replaced with another type in the hierarchy.
- mutable class members are allowed in the following cases:
    - mutex
    - `qx::subject<T>`
    - cache members

### Macros

- Try to solve the problem without a macro before adding a new one.
- All macros in qxLib must start with `QX_` and use `UPPER_CASE`.
- All macros taking arguments must require a trailing `;`. If the existing macro body cannot enforce this, append `QX_EMPTY_MACRO`.
- A macro intended for use inside a class body must leave access visibility set to `private`.

### Functions, methods

- `int foo()` is used, use `auto foo() -> int` only if a return type is dependent on an argument.
- Make a function `constexpr` whenever possible.
- Make a function `noexcept` whenever possible. Prefer return codes, values, `std::optional` and `std::expected` whenever possible.

## Other Coding Rules

- Do not use `using namespace XXX` throughout an entire file.
- Use `qx::string_view` instead of `const qx::string&`, `const qx::char_t*`, `const qx::char_t*, size_t`, `const qx::char_t[N]`, etc.
- Use `std::span<const T>` instead of `const container<T>&` wherever possible.
- Separate includes with blank lines in the following order: the corresponding library includes, then external library includes (including std).
- Use `qx::link` instead of `std::weak_ptr` wherever possible.
- Follow these rules when instantiating formatters:
    - Use `QX_FMT_NS` instead of the corresponding namespace (because the library supports both `std` and `fmt` formatting)
    - A specialization for `char_t` must be present, and `QX_STR_PREFIX` must be used where necessary (because the library supports both `char` and `wchar_t` as the main string type)
    - `-> decltype(ctx.out())` must be the explicit return type of `format` (otherwise `fmt` tries to explicitly instantiate templates it should not touch)
    ```cpp
    template<class char_t, class traits_t>
    struct QX_FMT_NS::formatter<qx::basic_string<char_t, traits_t>, char_t> : qx::basic_formatter<char_t>
    {
        template<class format_context_type>
        constexpr auto format(const qx::basic_string<char_t, traits_t>& value, format_context_type& ctx) const
            -> decltype(ctx.out())
        {
            return QX_FMT_NS::format_to(
                ctx.out(),
                QX_STR_PREFIX(char_t, "{}"),
                qx::basic_string_view<char_t>(value.data(), value.size()));
        }
    };
    ```

## Documentation

- All classes, functions, methods, and files must be properly documented.
- Avoid pointless documentation like `@param color - color`. Describe what this this is for, edge cases (if any), contracts (if any), and so on.
- Documentation may be omitted (but is not prohibited) for the following elements:
    - Structures (assumed to be simple enough to describe through their names).
    - Constructors and `init` methods without arguments.
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
    - Functions in namespace `details`.
    - Specializations of helper structures or functions (`std::hash`, `std::formatter`, etc.)
    - Builder return values (`*this`).
    - private methods
