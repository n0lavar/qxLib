set(_GTEST_HEADER_SEARCH_DIRS
    "${CMAKE_SOURCE_DIR}/../googletest/googletest/include"
)

# check environment variable
set(_GTEST_ENV_ROOT_DIR "$ENV{GTEST_ROOT_DIR}")

if(NOT GTEST_ROOT_DIR AND _GTEST_ENV_ROOT_DIR)
	set(GTEST_ROOT_DIR "${_GTEST_ENV_ROOT_DIR}")
endif(NOT GTEST_ROOT_DIR AND _GTEST_ENV_ROOT_DIR)

# put user specified location at beginning of search
if(GTEST_ROOT_DIR)
	set(_GTEST_HEADER_SEARCH_DIRS "${GTEST_ROOT_DIR}"
	"${GTEST_ROOT_DIR}/include"
	${_GTEST_HEADER_SEARCH_DIRS})
endif(GTEST_ROOT_DIR)

# locate header
find_path(GTEST_INCLUDE_DIR "gtest/gtest.h" PATHS ${_GTEST_HEADER_SEARCH_DIRS})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GTEST DEFAULT_MSG GTEST_INCLUDE_DIR)

if(GTEST_FOUND)
	set(GTEST_INCLUDE_DIRS "${GTEST_INCLUDE_DIR}")
    message(STATUS "GTEST_INCLUDE_DIR = ${GTEST_INCLUDE_DIR}")

    set(GTEST_LIBRARIES
        optimized   "${GTEST_INCLUDE_DIR}/../../build/lib/Release/gtest.lib"
        debug       "${GTEST_INCLUDE_DIR}/../../build/lib/Debug/gtestd.lib"
    )

endif(GTEST_FOUND)