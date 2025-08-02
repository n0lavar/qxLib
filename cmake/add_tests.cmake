
macro(add_tests
    # a cpp with the main() function
    _tests_main_cpp
    # a folder in VS where this test should be placed
    _ide_folder
    # tests cpps search pattern
    _glob_recurse_pattern
    _setup_test_target
)

    option(GENERATE_TESTS "Generate tests projects? Enabling this requires gtest" OFF)
    option(TEST_DEBUG_BREAKS "Should gtest hit a debug break when condition fails?" OFF)

    if (${GENERATE_TESTS})
        enable_testing()
        file(GLOB_RECURSE TEST_SRC_FILES "${_glob_recurse_pattern}")

        # from list of files we'll create tests name.gtest.cpp -> name
        foreach(_test_file ${TEST_SRC_FILES})
            get_filename_component(_test_name ${_test_file} NAME_WE)
            add_executable("${_test_name}" ${_test_file} "${_tests_main_cpp}")
            cmake_language(CALL ${_setup_test_target} ${_test_name})
            set_test_options(${_test_name})
            add_test(${_test_name} ${_test_name})
            set_target_properties (${_test_name} PROPERTIES 
                FOLDER "${_ide_folder}"
                VS_DEBUGGER_COMMAND_ARGUMENTS "$<$<BOOL:${TEST_DEBUG_BREAKS}>:--gtest_break_on_failure>"
            )
        endforeach()
    endif()

endmacro()
