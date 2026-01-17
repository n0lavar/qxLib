macro(add_benchmarks
    # a folder in VS where this benchmark should be placed
    _ide_folder
    # benchmark cpps search pattern
    _glob_recurse_pattern
)

    option(GENERATE_BENCHMARKS "Generate benchmarks projects? Enabling this requires benchmark" OFF)

    if (${GENERATE_BENCHMARKS})
        file(GLOB_RECURSE BENCHMARKS_SRC_FILES "${_glob_recurse_pattern}")

        # from list of files we'll create benchmarks name.bench.cpp -> name
        foreach(_file ${BENCHMARKS_SRC_FILES})
            get_filename_component(_target ${_file} NAME_WE)
            
            add_executable("${_target}" ${_file} ${FILES_NATVIS})

            target_include_directories(${_target} PRIVATE
                ${BENCHMARK_INCLUDE_DIR}
                ${GLM_INCLUDE_DIRS}
               "${CMAKE_CURRENT_LIST_DIR}/include/"
            )

            target_link_libraries(${_target} PRIVATE
                benchmark::benchmark
            )

            set_target_options(${_target})
            set_test_options(${_target})
                target_link_libraries(${_target} PRIVATE
                ${BENCHMARK_LIBRARIES}
            )

            if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
                target_compile_options(${_target} PRIVATE
                    /wd4266
                )
            endif()

            set_target_properties (${_target} PROPERTIES 
                FOLDER "${_ide_folder}"
            )
        endforeach()
    endif()

endmacro()
