
function(set_qxlib_target_options TARGET_)

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    
        target_link_libraries(${TARGET_} PRIVATE
            -pthread
        )
        
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
        
        target_compile_options(${TARGET_} PRIVATE
            $<$<CONFIG:Debug>:--coverage -O0 -g>
        )
        target_link_options(${TARGET_} PRIVATE 
            $<$<CONFIG:Debug>:--coverage>
        )
        target_link_libraries(${TARGET_} PRIVATE
            -pthread
        )
    
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Intel)
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    
        target_compile_options(${TARGET_} PRIVATE
            $<$<CONFIG:Debug>:/MTd /Od /Ob0 /Z7 /RTC1 /DDEBUG /D_DEBUG /DEBUG /bigobj>
            $<$<CONFIG:Release>:/MT /O2 /Ob2 /DNDEBUG>
        )
        
    endif()
    
    target_compile_features(${TARGET_} PRIVATE 
        cxx_std_17
    )
    set_target_properties(${TARGET_} PROPERTIES 
        LINKER_LANGUAGE CXX
    )
    target_link_libraries(${TARGET_} PRIVATE
        ${GTEST_LIBRARIES}
    )
    
endfunction()
