set(_GTEST_HEADER_SEARCH_DIRS
    "${EXTERNAL_FOLDER}/googletest/googletest/include"
    "${CMAKE_SOURCE_DIR}/../external/googletest/googletest/include"
    "${CMAKE_SOURCE_DIR}/../googletest/googletest/include"
    "${CMAKE_SOURCE_DIR}/googletest/googletest/include"
    
    "/usr/include"
    "/usr/local/include"
    "${CMAKE_SOURCE_DIR}/includes"
    "C:/Program Files (x86)/googletest" 
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
# Require a library as well as headers so configuration fails before linking.
find_library(GTEST_LIBRARY_RELEASE NAMES gtest PATHS
    "${GTEST_INCLUDE_DIR}/../../build/lib/Release"
    "${GTEST_INCLUDE_DIR}/../lib"
    "${GTEST_INCLUDE_DIR}/../lib/x86_64-linux-gnu"
)
find_library(GTEST_LIBRARY_DEBUG NAMES gtestd gtest PATHS
    "${GTEST_INCLUDE_DIR}/../../build/lib/Debug"
    "${GTEST_INCLUDE_DIR}/../lib"
    "${GTEST_INCLUDE_DIR}/../lib/x86_64-linux-gnu"
)
include(SelectLibraryConfigurations)
select_library_configurations(GTEST)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GTest DEFAULT_MSG GTEST_INCLUDE_DIR GTEST_LIBRARY)

if(GTest_FOUND)
    set(GTEST_INCLUDE_DIRS "${GTEST_INCLUDE_DIR}")
    set(GTEST_LIBRARIES "${GTEST_LIBRARY}")
endif()
