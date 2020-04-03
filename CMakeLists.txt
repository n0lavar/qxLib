# ================================================================
#                           qxLib
# ================================================================

cmake_minimum_required(VERSION 3.16)
project(qxLib)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

function(SET_TARGET_OPTIONS TARGET_)

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Intel)
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    
        target_compile_options(${TARGET_} PRIVATE
            $<$<CONFIG:Debug>:/MTd /Od /Ob0 /Z7 /RTC1 /DDEBUG /D_DEBUG /DEBUG /bigobj>
            $<$<CONFIG:Release>:/MT /O2 /Ob2 /DNDEBUG>
        )
        
    endif()
    
    target_compile_features(${TARGET_} PRIVATE 
        cxx_std_17
    )
    set_target_properties(${TARGET_} PROPERTIES 
        LINKER_LANGUAGE CXX
    )
    target_link_libraries(${TARGET_} PRIVATE
        ${GTEST_LIBRARIES}
    )
    
endfunction()

# ================================================================
# Containers
set (QXLIB_FILES_CONTAINERS
    include/qx/containers/iterator.h
    include/qx/containers/object_pool.h
    include/qx/containers/string.h
    include/qx/containers/string_traits.h
    include/qx/containers/container.h
    include/qx/containers/list_se.h
    include/qx/containers/vector2d.h
    include/qx/containers/triangular_vector.h
    
    include/qx/containers/object_pool.inl
    include/qx/containers/string.inl
    include/qx/containers/list_se.inl
    include/qx/containers/vector2d.inl
    include/qx/containers/triangular_vector.inl
)

source_group ("containers" FILES ${QXLIB_FILES_CONTAINERS})



# ================================================================
# OpenGL

set (QXLIB_FILES_GL

    include/qx/gl/qxgl.h

    include/qx/gl/buffer_base.h
    include/qx/gl/ubo.h
    include/qx/gl/ssbo.h
    include/qx/gl/ssbo_arrayed.h
    include/qx/gl/vao.h
    include/qx/gl/vbo.h
    include/qx/gl/ebo.h
    include/qx/gl/fbo.h
    include/qx/gl/rbo.h
    include/qx/gl/iBuffer.h
    include/qx/gl/shader_program.h
    include/qx/gl/shaders.h
    include/qx/gl/texture.h
    
    include/qx/gl/buffer_base.inl
    include/qx/gl/ubo.inl
    include/qx/gl/ssbo.inl
    include/qx/gl/ssbo_arrayed.inl
    include/qx/gl/vao.inl
    include/qx/gl/fbo.inl
    include/qx/gl/rbo.inl
    include/qx/gl/shader_program.inl
    include/qx/gl/shaders.inl
    include/qx/gl/texture.inl
)

source_group ("gl" FILES ${QXLIB_FILES_GL})



# ================================================================
# Algorithms

set (QXLIB_FILES_ALG
    include/qx/alg/numerical.h
    include/qx/alg/functional.h
    include/qx/alg/sort.h
)

source_group ("alg" FILES ${QXLIB_FILES_ALG})

# ================================================================
# Other
set (QXLIB_FILES_OTHER
    include/qx/other/singleton.h
    include/qx/other/logger.h
    include/qx/other/useful_macros.h
    include/qx/other/useful_funcs.h
    include/qx/other/typedefs.h
    include/qx/other/smart_enum.h
    include/qx/other/hashes.h
    include/qx/other/noncopyble.h
    include/qx/other/benchmark.h
    include/qx/other/random.h
    
    include/qx/other/logger.inl
    include/qx/other/hashes.inl
)

source_group ("other" FILES ${QXLIB_FILES_OTHER})



# ================================================================
# Temp
set (QXLIB_FILES_TEMP
    include/qx/temp/type_traits.h
)

source_group ("temp" FILES ${QXLIB_FILES_TEMP})



# ================================================================
# All

set (QXLIB_ALL_SOURCES
    ${QXLIB_FILES_CONTAINERS}
    ${QXLIB_FILES_GL}
    ${QXLIB_FILES_OTHER}
    ${QXLIB_FILES_ALG}
    ${QXLIB_FILES_TEMP}
    "${CMAKE_SOURCE_DIR}/tests/config.h"        
    "${CMAKE_SOURCE_DIR}/bench/bench_sort.h"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

find_package(GTEST REQUIRED)
find_package(Threads REQUIRED)
find_package(GLEW)
find_package(GLM)

include_directories(
    ${GTEST_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    "${CMAKE_SOURCE_DIR}/include/"
    "${CMAKE_SOURCE_DIR}/tests/"
    "${CMAKE_SOURCE_DIR}/bench/"
)

# ================================================================
# Setup Engine

add_library(qxLib ${QXLIB_ALL_SOURCES})

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")

    target_compile_options(qxLib PRIVATE
        -g -O0 --coverage
    )

    target_link_options(qxLib PRIVATE 
        --coverage
    )
    target_link_libraries(qxLib PRIVATE
        -pthread 
    )
    
    enable_testing()

    file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

    # from list of files we'll create tests test_name.cpp -> test_name
    foreach(_test_file ${TEST_SRC_FILES})
        if(NOT ${_test_file} STREQUAL ${PROJECT_SOURCE_DIR}/tests/main.cpp)
            get_filename_component(_test_name ${_test_file} NAME_WE)
            add_executable(${_test_name} ${_test_file} "${PROJECT_SOURCE_DIR}/tests/main.cpp")
            SET_TARGET_OPTIONS(${_test_name})
            target_link_libraries(${_test_name} PRIVATE qxLib)
            add_test(${_test_name} ${_test_name})
        endif()
    endforeach()
    
endif()
