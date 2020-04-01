# ================================================================
#                           qxLib
# ================================================================

cmake_minimum_required(VERSION 3.8)
project(qxLib)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

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
)

if(QX_DEBUG)

    SET(QXLIB_ALL_SOURCES 
        "${QXLIB_ALL_SOURCES}"
        "${CMAKE_SOURCE_DIR}/tests/main.cpp"
        "${CMAKE_SOURCE_DIR}/tests/config.h"

        "${CMAKE_SOURCE_DIR}/tests/test_sort.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_numerical.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_functional.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_list_se.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_object_pool.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_string.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_vector2d.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_triangular_vector.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_smart_enum.cpp"
        
        "${CMAKE_SOURCE_DIR}/bench/bench_sort.h"
    )

    find_package(GTEST REQUIRED)
    find_package(Threads REQUIRED)
    
    if(NOT MSVC)
        set(PThreadLib -pthread)
    endif()
    
    include_directories(
        ${GTEST_INCLUDE_DIR}
        "${CMAKE_SOURCE_DIR}/tests/"
        "${CMAKE_SOURCE_DIR}/bench/"
    )
    
endif(QX_DEBUG)


# ================================================================
# Setup Engine

find_package (GLEW)
find_package (GLM)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    "${CMAKE_SOURCE_DIR}/include/"
)

add_executable(qxLib ${QXLIB_ALL_SOURCES})

target_compile_features(qxLib PRIVATE 
    cxx_std_17
)

set_target_properties(qxLib PROPERTIES 
    LINKER_LANGUAGE CXX
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(qxLib PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:/std:c++17>
        $<$<CONFIG:Debug>:/MTd /Od /Ob0 /Z7 /RTC1 /DDEBUG /D_DEBUG /DEBUG /bigobj>
        $<$<CONFIG:Release>:/MT /O2 /Ob2 /DNDEBUG>
    )
endif()


if(QX_DEBUG)

    target_compile_options(qxLib PRIVATE
        -O0        # no optimization
        -g         # generate debug info
        --coverage # sets all required flags
    )

    target_link_libraries (qxLib --coverage
        ${PThreadLib}
        ${GTEST_LIBRARIES}
    )
        
endif(QX_DEBUG)
