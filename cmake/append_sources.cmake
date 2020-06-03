set(ALL_SOURCES "")
set(ALL_INCLUDE_DIRS "")

macro(append_sources SOURCES_)

    set(ALL_SOURCES 
        ${ALL_SOURCES} 
        ${SOURCES_} 
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    PARENT_SCOPE)
    
    set(ALL_INCLUDE_DIRS 
        ${ALL_INCLUDE_DIRS} 
        ${CMAKE_CURRENT_SOURCE_DIR} 
    PARENT_SCOPE)
    
endmacro()

macro(clear_sources_vars)

    set(ALL_SOURCES "")
    set(ALL_INCLUDE_DIRS "")
    
endmacro()
