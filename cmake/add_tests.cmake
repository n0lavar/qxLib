macro(set_test_options _target)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    
        target_link_libraries(${_target} PRIVATE
            -pthread 
            -lstdc++fs
        )
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
        
        target_link_options(${_target} PRIVATE 
            $<$<CONFIG:Debug>:--coverage>
        )
        
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:--coverage -fkeep-inline-functions -fkeep-static-consts>
        )
        
        target_link_libraries(${_target} PRIVATE
            -pthread 
			-lstdc++fs
        )
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    
        target_compile_options(${_target} PRIVATE
            /bigobj
        )
    endif()
            
    target_link_libraries(${_target} PRIVATE
        ${GTEST_LIBRARIES}
    )
endmacro()

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
            get_filename_component(_target ${_test_file} NAME_WE)
            set(_target "${_target}.gtest")
            add_executable("${_target}" ${_test_file} "${_tests_main_cpp}" ${FILES_NATVIS} ${PVSCONFIG_FILE})
            cmake_language(CALL ${_setup_test_target} ${_target})
            set_test_options(${_target})
            add_test(${_target} ${_target})
            set_target_properties (${_target} PROPERTIES 
                FOLDER "${_ide_folder}"
                VS_DEBUGGER_COMMAND_ARGUMENTS "$<$<BOOL:${TEST_DEBUG_BREAKS}>:--gtest_break_on_failure> --gtest_catch_exceptions=0"
            )
        endforeach()
    endif()
endmacro()
