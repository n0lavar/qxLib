cmake_minimum_required(VERSION 3.16)
project(qxLib)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_DEBUG_POSTFIX d)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
if (NOT DEFINED EXTERNAL_FOLDER)
    set (EXTERNAL_FOLDER "${CMAKE_CURRENT_LIST_DIR}/../external")
    if (NOT IS_DIRECTORY "${EXTERNAL_FOLDER}" AND IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../../external")
        set(EXTERNAL_FOLDER "${CMAKE_CURRENT_LIST_DIR}/../../external")
    endif()
endif()
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${EXTERNAL_FOLDER}")

include(cmake/set_target_options.cmake)
include(cmake/add_tests.cmake)
include(cmake/add_benchmarks.cmake)

set_source_files_properties(.pvsconfig PROPERTIES HEADER_FILE_ONLY TRUE)

# ================================================================
# Collect sources

file(GLOB_RECURSE FILES_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/qx/*.h)
file(GLOB_RECURSE FILES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/include/qx/*.cpp)
file(GLOB_RECURSE FILES_INLINES ${CMAKE_CURRENT_SOURCE_DIR}/include/qx/*.inl)
file(GLOB_RECURSE FILES_NATVIS  ${CMAKE_CURRENT_SOURCE_DIR}/include/qx/*.natvis)
set(PVSCONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/include/qx/.pvsconfig")

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/qx
    FILES ${FILES_HEADERS} ${FILES_SOURCES} ${FILES_INLINES} ${FILES_NATVIS} ${PVSCONFIG_FILE}
)


# ================================================================
# Setup

find_package(Threads REQUIRED)

find_package(Boost)
if(NOT Boost_FOUND)
    set(Boost_ROOT "${EXTERNAL_FOLDER}/boost")
    find_package(Boost)
endif()

find_package(GLM REQUIRED)
find_package(FMT)


add_library(qxLib ${FILES_HEADERS} ${FILES_SOURCES} ${FILES_INLINES} ${FILES_NATVIS} ${PVSCONFIG_FILE})
target_compile_features(qxLib PUBLIC cxx_std_23)

macro(qx_setup_test_target _target)
    target_include_directories(${_target} PRIVATE
        ${GTEST_INCLUDE_DIR}
        ${GLM_INCLUDE_DIRS}
        ${FMT_INCLUDE_DIRS}
        "${CMAKE_CURRENT_LIST_DIR}/include/"
        "${CMAKE_CURRENT_LIST_DIR}/tests/"
    )

    if(Boost_FOUND)
        target_include_directories(${_target} PRIVATE
            ${Boost_INCLUDE_DIRS}
        ) 
    endif()

    set_target_options(${_target})
endmacro()

option(QX_GENERATE_TESTS "Generate qxLib tests? Enabling this requires gtest" OFF)

enable_testing()

add_tests(
    "${QX_GENERATE_TESTS}"
    "${PROJECT_SOURCE_DIR}/tests/main.cpp" 
    "qxLibTests" 
    "${PROJECT_SOURCE_DIR}/tests/*.gtest.cpp"
    qx_setup_test_target
)

add_benchmarks(
    "qxLibBenchmarks" 
    "${PROJECT_SOURCE_DIR}/benchmarks/*.bench.cpp"
)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_custom_target(RegenerateSolution
        COMMAND "${CMAKE_COMMAND}" -S "${CMAKE_SOURCE_DIR}" -B "${CMAKE_BINARY_DIR}"
        VERBATIM
    )
    set_target_properties(RegenerateSolution PROPERTIES
        FOLDER "Tools"
    )
endif()
