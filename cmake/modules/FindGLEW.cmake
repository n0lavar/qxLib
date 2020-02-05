set(_glew_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include"
    "${CMAKE_SOURCE_DIR}/includes"
    "${CMAKE_SOURCE_DIR}/../glew/include/GL/"
    "C:/Program Files (x86)/glew" 
)

# check environment variable
set(_GLEW_ENV_ROOT_DIR "$ENV{GLEW_ROOT_DIR}")

if(NOT GLEW_ROOT_DIR AND _GLEW_ENV_ROOT_DIR)
	set(GLEW_ROOT_DIR "${_GLEW_ENV_ROOT_DIR}")
endif(NOT GLEW_ROOT_DIR AND _GLEW_ENV_ROOT_DIR)

# put user specified location at beginning of search
if(GLEW_ROOT_DIR)
	set(_glew_HEADER_SEARCH_DIRS "${GLEW_ROOT_DIR}"
	"${GLEW_ROOT_DIR}/include"
	${_glew_HEADER_SEARCH_DIRS})
endif(GLEW_ROOT_DIR)

# locate header
find_path(GLEW_INCLUDE_DIR "glew.h" PATHS ${_glew_HEADER_SEARCH_DIRS})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_INCLUDE_DIR)

if(GLEW_FOUND)
	set(GLEW_INCLUDE_DIRS "${GLEW_INCLUDE_DIR}")
	message(STATUS "GLEW_INCLUDE_DIR = ${GLEW_INCLUDE_DIR}")
endif(GLEW_FOUND)