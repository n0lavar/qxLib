set(_FMT_HEADER_SEARCH_DIRS
    "${EXTERNAL_FOLDER}/fmt/include"
    "${CMAKE_SOURCE_DIR}/../external/fmt/include"
    "${CMAKE_SOURCE_DIR}/../fmt/include"
    "${CMAKE_SOURCE_DIR}/fmt/include"
    
    "/usr/include"
    "/usr/local/include"
    "${CMAKE_SOURCE_DIR}/includes"
    "C:/Program Files (x86)/fmt" 
)

# check environment variable
set(_FMT_ENV_ROOT_DIR "$ENV{FMT_ROOT_DIR}")

if(NOT FMT_ROOT_DIR AND _FMT_ENV_ROOT_DIR)
	set(FMT_ROOT_DIR "${_FMT_ENV_ROOT_DIR}")
endif(NOT FMT_ROOT_DIR AND _FMT_ENV_ROOT_DIR)

# put user specified location at beginning of search
if(FMT_ROOT_DIR)
	set(_FMT_HEADER_SEARCH_DIRS "${FMT_ROOT_DIR}"
	"${FMT_ROOT_DIR}/include"
	${_FMT_HEADER_SEARCH_DIRS})
endif(FMT_ROOT_DIR)

# locate header
find_path(FMT_INCLUDE_DIR "fmt/fmt-c.h" PATHS ${_FMT_HEADER_SEARCH_DIRS})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FMT DEFAULT_MSG FMT_INCLUDE_DIR)

if(FMT_FOUND)
	set(FMT_INCLUDE_DIRS "${FMT_INCLUDE_DIR}")
endif(FMT_FOUND)
