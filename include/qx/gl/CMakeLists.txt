
set(FOLDER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ibuffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/buffer_base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ubo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ssbo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vao.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vbo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ebo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fbo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rbo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shader_program.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders.h
    ${CMAKE_CURRENT_SOURCE_DIR}/texture.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/buffer_base.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/ubo.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/ssbo.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/vao.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/fbo.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/rbo.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/shader_program.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/texture.inl

)

append_sources("${FOLDER_FILES}")