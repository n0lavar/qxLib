cmake_minimum_required(VERSION 3.16)
project(qxLib)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_DEBUG_POSTFIX d)

cmake_policy(SET CMP0167 OLD)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
if (NOT DEFINED EXTERNAL_FOLDER)
    set (EXTERNAL_FOLDER "${CMAKE_CURRENT_LIST_DIR}/../external")
endif()
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${EXTERNAL_FOLDER}")

include(cmake/set_target_options.cmake)
include(cmake/set_test_options.cmake)
include(cmake/add_tests.cmake)


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

find_package(Boost 1.79)
find_package(GTest MODULE)
find_package(Threads REQUIRED)
find_package(GLM)

add_library(qxLib ${FILES_HEADERS} ${FILES_SOURCES} ${FILES_INLINES})

macro(qx_setup_test_target _target)
    target_include_directories(${_target} PRIVATE
        ${GTEST_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
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

add_tests(
    "${PROJECT_SOURCE_DIR}/tests/main.cpp" 
    "qxLibTests" 
    "${PROJECT_SOURCE_DIR}/tests/*.gtest.cpp"
    qx_setup_test_target
)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)

    add_custom_target(RegenerateSolution
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Tools/generate_sln.py
    )
    set_target_properties(RegenerateSolution PROPERTIES
        FOLDER "Tools"
    )
endif()
