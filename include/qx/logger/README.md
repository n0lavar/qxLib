# qx::logger

A stream-based logging system for C++ projects: collects messages via the `QX_LOG` macro and sends them to all registered streams.

Features:
- Categories and file categories:  
  Categories are used to structure code. Messages that share the same category belong to one logical block.  
  The system uses the concept of "file categories", which is also used in asserts and perf scopes. A category declared once at the top of a file...
  ```
  QX_SET_FILE_CATEGORY(CatMySystem);
  ```
  ...is used by all `QX_LOG` in that file.  
  If no category is specified, the default category `CatDefault` is used.  
  You can also specify a category manually using `QX_LOG_C`, which will override the file category.
- Multiple streams and extensibility:  
  You can add multiple streams to your logger, including ones provided by the library (output to standard output, to a file, and to the debug window in your IDE) or custom ones. You can also override the global logger used by `QX_LOG` with your own implementation.
- Per-category settings: filtering and formatting:  
  Messages can be filtered on two levels: using compile-time or runtime verbosity.  
  - The first parameter is specified in each category using `set_verbosity()` (default value is `qx::verbosity::log`) and allows filtering a message before the program even runs. By setting the `QX_CONF_COMPILE_TIME_VERBOSITY` macro to `qx::verbosity::none`, you can completely remove all logging traces from the program, including string literals;
  - Runtime verbosity can be set using `qx::logger::register_category` and is checked during execution. This is convenient for adjusting logging levels via a config. Here you can also set other settings for messages of a specific category, for example a custom formatting function.
- Logging levels:  
  ```
  enum class verbosity
  {
      detailed,  // very frequently repeated messages, for example, on every update
      verbose,   // messages you don't want to be displayed by default
      log,       // default level
      important, // same as log but highlighted if possible
      warning,   // not yet an error, but something to look out for
      error,     // an error after which it is possible to continue the program
      critical,  // an error that makes it impossible to continue the program
      none,      // message is not displayed
  };
  ```
- Performance:  
  A lot of attention is paid to system performance.
    - Allocations:  
      - The logger uses a pool of preallocated strings for messages; allocation only occurs if there are not enough strings;
      - During logging, neither the logger nor its streams (provided by the library) allocate memory;
      - User callbacks also have an option to avoid allocations.
    - Using small buffer object optimization for polymorphic objects (`qx::sbo_poly`), all streams are stored cache-locally in a single `std::vector`, even though they are different objects;
    - Streams implement memory mapping for the file logger and `fwrite` output for standard output. While on Linux all streams have roughly the same performance, on MSVC these approaches significantly improve performance compared to `ofstream` and `cout` streams;
    - By default, the logger and all streams are thread-safe. If you are sure that you do not need the overhead (for example, you only have one stream or you send all logging to a separate stream), you can slightly improve performance by turning off synchronisation using the bProtectLog flag.

## Usage

Minimal working example:
```
#include <qx/logger/logger.h>

QX_LOG(qx::verbosity::log, "The answer is {}", 42);
```
This will create a default logger with a standard output stream and print the message to it.

### Custom streams

You can add new streams, for example to output to the IDE debug window or to a file.
```
qx::logger& logger = qx::get_logger();
logger.add_stream(qx::debugger_logger_stream());
logger.add_stream(qx::file_logger_stream_mapping());
```
Or implement your own stream and add it the same way:
```
class my_logger_stream : public qx::base_logger_stream
{
    virtual void do_log(...) override;
    virtual void do_flush() override;
};
logger.add_stream(my_logger_stream());
```

### Custom logger

If streams define where messages go, the logger defines how they get there. By implementing your own logger, you can add additional filtering, formatting, or asynchronous execution.
```
class my_logger final
    : public qx::logger
    , public qx::singleton<my_logger>
{
    // custom logic...
};

my_logger& logger = my_logger::get_instance();
logger.reset();
// set it up...
qx::g_pGlobalLogger = &logger;
```

## Stream performance comparison

While on Linux all compilers (and standard libraries) give roughly the same results for streams performing the same work (`qx::cout_logger_stream` and `qx::fwrite_logger_stream`, `qx::file_logger_stream_ofstream` and `qx::file_logger_stream_fopen` and `qx::file_logger_stream_mapping`), on Windows with MSVC the situation is much worse. `std::ofstream` performs significantly worse than the `fopen` solution, which in turn is slightly worse than a manually implemented file memory mapping approach if its size is predefined.

<details>
    <summary>Ubuntu (clang)</summary>

    Running ./build/logger_streams.bench
    2026-01-18T16:56:09+00:00
    Running ./build/logger_streams.bench
    Run on (4 X 3491.52 MHz CPU s)
    CPU Caches:
    L1 Data 48 KiB (x2)
    L1 Instruction 32 KiB (x2)
    L2 Unified 1280 KiB (x2)
    L3 Unified 49152 KiB (x1)
    Load Average: 3.32, 1.58, 0.65
    ------------------------------------------------------------------------------------------------------------------
    Benchmark                                                                        Time             CPU   Iterations
    ------------------------------------------------------------------------------------------------------------------
    logger_stream_fixture<traits::debugger>/bench/1000                        12392295 ns     12387851 ns           56
    logger_stream_fixture<traits::cout>/bench/1000                            14479304 ns     14476901 ns           48
    logger_stream_fixture<traits::fwrite>/bench/1000                          13886544 ns     13885281 ns           50
    logger_stream_fixture<traits::ostream_default_buffer>/bench/1000          12790522 ns     12790103 ns           54
    logger_stream_fixture<traits::ostream>/bench/1000                         12898660 ns     12897926 ns           54
    logger_stream_fixture<traits::fopen_default_buffer>/bench/1000            12830989 ns     12830083 ns           55
    logger_stream_fixture<traits::fopen>/bench/1000                           12591758 ns     12591093 ns           55
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/1000    13086803 ns     13085556 ns           55
    logger_stream_fixture<traits::mapping>/bench/1000                         12759345 ns     12758898 ns           55
    logger_stream_fixture<traits::debugger>/bench/5000                        61354469 ns     61350565 ns           11
    logger_stream_fixture<traits::cout>/bench/5000                            72160327 ns     72158325 ns           10
    logger_stream_fixture<traits::fwrite>/bench/5000                          70071930 ns     70066058 ns           10
    logger_stream_fixture<traits::ostream_default_buffer>/bench/5000          63918806 ns     63908402 ns           11
    logger_stream_fixture<traits::ostream>/bench/5000                         64097400 ns     64090902 ns           11
    logger_stream_fixture<traits::fopen_default_buffer>/bench/5000            63467459 ns     63460810 ns           11
    logger_stream_fixture<traits::fopen>/bench/5000                           63117117 ns     63112233 ns           11
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/5000    64026371 ns     64022825 ns           11
    logger_stream_fixture<traits::mapping>/bench/5000                         64197686 ns     64193719 ns           11
    logger_stream_fixture<traits::debugger>/bench/10000                      122421033 ns    122419999 ns            6
    logger_stream_fixture<traits::cout>/bench/10000                          144564738 ns    144554038 ns            5
    logger_stream_fixture<traits::fwrite>/bench/10000                        138976061 ns    138967272 ns            5
    logger_stream_fixture<traits::ostream_default_buffer>/bench/10000        128154483 ns    128145989 ns            6
    logger_stream_fixture<traits::ostream>/bench/10000                       128326785 ns    128321575 ns            5
    logger_stream_fixture<traits::fopen_default_buffer>/bench/10000          127617219 ns    127604507 ns            6
    logger_stream_fixture<traits::fopen>/bench/10000                         126721708 ns    126712960 ns            6
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/10000  127952564 ns    127935309 ns            5
    logger_stream_fixture<traits::mapping>/bench/10000                       129575970 ns    129575066 ns            5
    logger_stream_fixture<traits::debugger>/bench/20000                      245142459 ns    245118036 ns            3
    logger_stream_fixture<traits::cout>/bench/20000                          289364629 ns    289355921 ns            2
    logger_stream_fixture<traits::fwrite>/bench/20000                        278702647 ns    278691554 ns            3
    logger_stream_fixture<traits::ostream_default_buffer>/bench/20000        256517873 ns    256491330 ns            3
    logger_stream_fixture<traits::ostream>/bench/20000                       256437733 ns    256427426 ns            3
    logger_stream_fixture<traits::fopen_default_buffer>/bench/20000          256211234 ns    256176528 ns            3
    logger_stream_fixture<traits::fopen>/bench/20000                         255902184 ns    255894350 ns            3
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/20000  256669392 ns    256651326 ns            3
    logger_stream_fixture<traits::mapping>/bench/20000                       256310182 ns    256289879 ns            3
    logger_stream_fixture<traits::debugger>/bench/40000                      492038861 ns    491985827 ns            2
    logger_stream_fixture<traits::cout>/bench/40000                          576448279 ns    576408182 ns            1
    logger_stream_fixture<traits::fwrite>/bench/40000                        554293283 ns    554218324 ns            1
    logger_stream_fixture<traits::ostream_default_buffer>/bench/40000        511484244 ns    511426464 ns            1
    logger_stream_fixture<traits::ostream>/bench/40000                       510297541 ns    510291312 ns            1
    logger_stream_fixture<traits::fopen_default_buffer>/bench/40000          507632557 ns    507574312 ns            1
    logger_stream_fixture<traits::fopen>/bench/40000                         502452887 ns    502366132 ns            1
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/40000  510412730 ns    510396303 ns            1
    logger_stream_fixture<traits::mapping>/bench/40000                       511170081 ns    511153539 ns            1
    logger_stream_fixture<traits::debugger>/bench/80000                      979965472 ns    979882066 ns            1
    logger_stream_fixture<traits::cout>/bench/80000                         1150113885 ns   1150017589 ns            1
    logger_stream_fixture<traits::fwrite>/bench/80000                       1108897418 ns   1108780803 ns            1
    logger_stream_fixture<traits::ostream_default_buffer>/bench/80000       1027582643 ns   1027526048 ns            1
    logger_stream_fixture<traits::ostream>/bench/80000                      1020601713 ns   1020557163 ns            1
    logger_stream_fixture<traits::fopen_default_buffer>/bench/80000         1017106736 ns   1017028214 ns            1
    logger_stream_fixture<traits::fopen>/bench/80000                        1014441524 ns   1014378444 ns            1
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/80000 1026482290 ns   1026393309 ns            1
    logger_stream_fixture<traits::mapping>/bench/80000                      1037220955 ns   1037085852 ns            1
</details>

<details>
    <summary>Windows (MSVC)</summary>

    Running D:\a\qxLib\qxLib\build\Release\logger_streams.bench.exe
    Run on (4 X 2445 MHz CPU s)
    CPU Caches:
    L1 Data 32 KiB (x2)
    L1 Instruction 32 KiB (x2)
    L2 Unified 512 KiB (x2)
    L3 Unified 32768 KiB (x1)
    ------------------------------------------------------------------------------------------------------------------
    Benchmark                                                                        Time             CPU   Iterations
    ------------------------------------------------------------------------------------------------------------------
    logger_stream_fixture<traits::debugger>/bench/1000                         1370487 ns      1395089 ns          560
    logger_stream_fixture<traits::cout>/bench/1000                           114108017 ns    111979167 ns            6
    logger_stream_fixture<traits::fwrite>/bench/1000                           6295351 ns      6184896 ns           96
    logger_stream_fixture<traits::ostream_default_buffer>/bench/1000          14511844 ns     14236111 ns           45
    logger_stream_fixture<traits::ostream>/bench/1000                         12768632 ns     12555804 ns           56
    logger_stream_fixture<traits::fopen_default_buffer>/bench/1000             1881666 ns      1885054 ns          373
    logger_stream_fixture<traits::fopen>/bench/1000                            1612900 ns      1534598 ns          448
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/1000     1607114 ns      1574017 ns          407
    logger_stream_fixture<traits::mapping>/bench/1000                          1534554 ns      1534598 ns          448
    logger_stream_fixture<traits::debugger>/bench/5000                         6249400 ns      6138393 ns          112
    logger_stream_fixture<traits::cout>/bench/5000                           559714000 ns    546875000 ns            1
    logger_stream_fixture<traits::fwrite>/bench/5000                          29718400 ns     29296875 ns           24
    logger_stream_fixture<traits::ostream_default_buffer>/bench/5000          69233100 ns     69602273 ns           11
    logger_stream_fixture<traits::ostream>/bench/5000                         63406644 ns     62500000 ns            9
    logger_stream_fixture<traits::fopen_default_buffer>/bench/5000             9432944 ns      9277344 ns           64
    logger_stream_fixture<traits::fopen>/bench/5000                            8379212 ns      8333333 ns           90
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/5000     8133509 ns      8159722 ns           90
    logger_stream_fixture<traits::mapping>/bench/5000                          7629291 ns      7638889 ns           90
    logger_stream_fixture<traits::debugger>/bench/10000                       12710314 ns     12276786 ns           56
    logger_stream_fixture<traits::cout>/bench/10000                         1119092800 ns   1109375000 ns            1
    logger_stream_fixture<traits::fwrite>/bench/10000                         61433840 ns     56250000 ns           10
    logger_stream_fixture<traits::ostream_default_buffer>/bench/10000        136971140 ns    137500000 ns            5
    logger_stream_fixture<traits::ostream>/bench/10000                       127563783 ns    127604167 ns            6
    logger_stream_fixture<traits::fopen_default_buffer>/bench/10000           18880462 ns     19003378 ns           37
    logger_stream_fixture<traits::fopen>/bench/10000                          16145536 ns     16319444 ns           45
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/10000   15915342 ns     15625000 ns           45
    logger_stream_fixture<traits::mapping>/bench/10000                        15256425 ns     15345982 ns           56
    logger_stream_fixture<traits::debugger>/bench/20000                       25326546 ns     25669643 ns           28
    logger_stream_fixture<traits::cout>/bench/20000                         2251598500 ns   2250000000 ns            1
    logger_stream_fixture<traits::fwrite>/bench/20000                        119008333 ns    114583333 ns            6
    logger_stream_fixture<traits::ostream_default_buffer>/bench/20000        275717550 ns    273437500 ns            2
    logger_stream_fixture<traits::ostream>/bench/20000                       255646800 ns    255208333 ns            3
    logger_stream_fixture<traits::fopen_default_buffer>/bench/20000           37820263 ns     37006579 ns           19
    logger_stream_fixture<traits::fopen>/bench/20000                          32169482 ns     32670455 ns           22
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/20000   32409171 ns     31994048 ns           21
    logger_stream_fixture<traits::mapping>/bench/20000                        30695368 ns     31250000 ns           22
    logger_stream_fixture<traits::debugger>/bench/40000                       50548336 ns     51136364 ns           11
    logger_stream_fixture<traits::cout>/bench/40000                         4482839700 ns   4468750000 ns            1
    logger_stream_fixture<traits::fwrite>/bench/40000                        239313200 ns    239583333 ns            3
    logger_stream_fixture<traits::ostream_default_buffer>/bench/40000        549498000 ns    546875000 ns            1
    logger_stream_fixture<traits::ostream>/bench/40000                       511593800 ns    515625000 ns            1
    logger_stream_fixture<traits::fopen_default_buffer>/bench/40000           76543289 ns     76388889 ns            9
    logger_stream_fixture<traits::fopen>/bench/40000                          64679764 ns     65340909 ns           11
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/40000   64404500 ns     63920455 ns           11
    logger_stream_fixture<traits::mapping>/bench/40000                        61811436 ns     61079545 ns           11
    logger_stream_fixture<traits::debugger>/bench/80000                      102893286 ns    102678571 ns            7
    logger_stream_fixture<traits::cout>/bench/80000                         8967926600 ns   8953125000 ns            1
    logger_stream_fixture<traits::fwrite>/bench/80000                        477235850 ns    476562500 ns            2
    logger_stream_fixture<traits::ostream_default_buffer>/bench/80000       1101274000 ns   1093750000 ns            1
    logger_stream_fixture<traits::ostream>/bench/80000                      1027931000 ns   1015625000 ns            1
    logger_stream_fixture<traits::fopen_default_buffer>/bench/80000          152094375 ns    152343750 ns            4
    logger_stream_fixture<traits::fopen>/bench/80000                         128306650 ns    127604167 ns            6
    logger_stream_fixture<traits::mapping_default_initial_size>/bench/80000  129836740 ns    131250000 ns            5
    logger_stream_fixture<traits::mapping>/bench/80000                       126508233 ns    127604167 ns            6
</details>

## FAQ

### Why a macro?

The macro allows several important things:
- Automatically extract the file category;
- Compare the passed verbosity and the category verbosity in a `constexpr` context;
- Convert ``__FUNCTION__`` to `qx::string_view` even on Linux (where it is not a char array and cannot be simply wrapped in `QXT()`)

### Why doesn't the library include separate threading, asynchronicity, etc. for the logger?

Although this could significantly improve performance, I believe that every system should do only one thing, but do it well. Creating new threads or implementing your own asynchronous system is not what I want to focus on. The library is generally intended for use in various game engines, and they usually already have these systems.  
The best solution in this case is to inherit from `qx::logger` as shown in the "Custom logger" section and override the `log` method. In my stress test (enabling all logs at `detailed` during multithreaded loading), I managed to reduce the total logger runtime from 44.17 seconds to 15.01 for 299731 log lines by moving everything except string formatting to a single thread.
