
set(FOLDER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/singleton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/useful_macros.h
    ${CMAKE_CURRENT_SOURCE_DIR}/useful_funcs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/typedefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/smart_enum.h
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark.h
    ${CMAKE_CURRENT_SOURCE_DIR}/random.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rtti.h
    ${CMAKE_CURRENT_SOURCE_DIR}/type_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h

    ${CMAKE_CURRENT_SOURCE_DIR}/logger.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy_main.cpp
)

append_sources("${FOLDER_FILES}")