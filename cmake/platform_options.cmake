
function(set_qxlib_target_options _target)

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    
        target_compile_options(${_target} PRIVATE
            -lc++fs
        )
        target_link_libraries(${_target} PRIVATE
            -pthread
        )
        
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
        
        target_compile_options(${_target} PRIVATE
			-lstdc++fs
            $<$<CONFIG:Debug>:--coverage -O0 -g>
        )
        target_link_options(${_target} PRIVATE 
            $<$<CONFIG:Debug>:--coverage>
        )
        target_link_libraries(${_target} PRIVATE
            -pthread
        )
    
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:/MTd /Od /Ob0 /Z7 /RTC1 /DDEBUG /D_DEBUG /DEBUG /bigobj>
            $<$<CONFIG:Release>:/MT /O2 /Ob2 /DNDEBUG>
            $<$<CONFIG:RelWithDebInfo>:/MT>
            $<$<CONFIG:MinSizeRel>:/MT>
        )
        
    endif()
        
    target_compile_features(${_target} PRIVATE 
        cxx_std_17
    )
    
    set_target_properties(${_target} PROPERTIES 
        LINKER_LANGUAGE CXX
    )
    
    target_link_libraries(${_target} PRIVATE
        ${GTEST_LIBRARIES}
    )
    
endfunction()

