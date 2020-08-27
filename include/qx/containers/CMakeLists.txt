
set(FOLDER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/iterator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/string.h
    ${CMAKE_CURRENT_SOURCE_DIR}/string_traits.h
    ${CMAKE_CURRENT_SOURCE_DIR}/container.h
    ${CMAKE_CURRENT_SOURCE_DIR}/list_se.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vector2d.h
    ${CMAKE_CURRENT_SOURCE_DIR}/triangular_vector.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/string.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/list_se.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/vector2d.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/triangular_vector.inl

)

append_sources("${FOLDER_FILES}")