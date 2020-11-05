# ================================================================
#                           qxLib
# ================================================================

cmake_minimum_required(VERSION 3.16)
project(qxLib)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")
include(cmake/platform_options.cmake)


# ================================================================
# Options

option(GENERATE_TESTS "Generate tests projects? Enabling this requires gtest" OFF)


# ================================================================
# Collect sources

file(GLOB_RECURSE FILES_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/qx/*.h)
file(GLOB_RECURSE FILES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/include/qx/*.cpp)
file(GLOB_RECURSE FILES_INLINES ${CMAKE_CURRENT_SOURCE_DIR}/include/qx/*.inl)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/qx
    FILES ${FILES_HEADERS} ${FILES_SOURCES} ${FILES_INLINES}
)


# ================================================================
# Setup

find_package(GTEST REQUIRED)
find_package(Threads REQUIRED)
find_package(GLEW)
find_package(GLM)

include_directories(
    ${GTEST_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    "${CMAKE_CURRENT_LIST_DIR}/include/"
    "${CMAKE_CURRENT_LIST_DIR}/tests/"
)

add_library(qxLib ${FILES_HEADERS} ${FILES_SOURCES} ${FILES_INLINES})
set_qxlib_target_options(qxLib)


# ================================================================
# add tests

if (${GENERATE_TESTS})
    enable_testing()
    file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

    # from list of files we'll create tests test_name.cpp -> test_name
    foreach(_test_file ${TEST_SRC_FILES})
        if(NOT ${_test_file} STREQUAL ${PROJECT_SOURCE_DIR}/tests/main.cpp)
            get_filename_component(_test_name ${_test_file} NAME_WE)
            add_executable("${_test_name}" ${_test_file} "${PROJECT_SOURCE_DIR}/tests/main.cpp")
            set_qxlib_target_options(${_test_name})
            add_test(${_test_name} ${_test_name})
            set_target_properties (${_test_name} PROPERTIES FOLDER qxLibTests)
        endif()
    endforeach()
endif()