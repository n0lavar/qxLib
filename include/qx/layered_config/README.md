# qx::layered_config

A layered configuration system for C++ projects: declare configuration variables once, then read their values from defaults, environment variables, command line arguments, or runtime overrides.

Features:
- Configuration variables with metadata:  
  Each variable has a runtime name and can optionally have an environment variable name, command line names, a help group, a description, and a required flag.
- Several value layers:  
  Values can come from:
  - the default value passed to `layered_config_variable_builder`;
  - environment variables;
  - command line arguments;
  - runtime `get()` / `set()` calls.
- Typed access:  
  Variables are declared with their C++ type and returned as that type. Common cases include `int`, `size_t`, `float`, `bool`, and `qx::cstring_view`.
- Command line parsing:  
  The parser accepts:
  ```
  --key
  -k
  --key=value
  -k=value
  --key value
  -k value
  ```
  A flag without an explicit value is treated as `true`.
- Help output:  
  Variables can be grouped and described. If `--help` or `-h` is present, `show_help()` logs a generated usage message through `qx::logger`.
- Required variables:  
  If a variable is marked as required and no valid value is provided, `parse()` logs an error and returns `false`.

## Usage

Minimal working example:
```cpp
#include <qx/layered_config/layered_config_variable.h>

// Variables should usually be declared once and stored globally.
// Runtime-mutable variables should be non-const.
const qx::layered_config_variable k_lcJobs =
    qx::layered_config_variable_builder<size_t>("jobs", 4)
        .env("MY_APP_JOBS")
        .command_line("--jobs", "-j")
        .description("Number of worker jobs")
        .build();

int main(int argc, char* argv[])
{
    qx::layered_configs_manager& config = qx::layered_configs_manager::get_instance();

    // Set command line arguments. This doesn't parse it, but allows you to show help.
    config.set_args(argc, argv);

    // Show help if required. 
    // If this method returns true, a help message was shown, usually you want to close your app after this.
    if (config.show_help())
        return 0;

    // Parse envs and command lines. If some required arguments are missing, this method returns false.
    if (!config.parse())
        return 1;

    // You can access values now.
    // The priorities of layers is:
    // 1. Runtime
    // 2. Command line
    // 3. Environment variables
    // 4. Default value
    const size_t nJobs = g_lcJobs.get();

    ...

    return 0;
}
```

This creates a variable named `jobs` with default value `4`. It can be overridden by `MY_APP_JOBS`, `--jobs=8`, `--jobs 8`, `-j=8`, or `-j 8`.
