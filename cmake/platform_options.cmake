
function(set_qxlib_target_options _target)

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    
        target_link_libraries(${_target} PRIVATE
            -pthread 
			-lstdc++fs
        )
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:-D_DEBUG=1>
            $<$<CONFIG:Release>:-D_DEBUG=0>
        )
        
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
        
        target_link_options(${_target} PRIVATE 
            $<$<CONFIG:Debug>:--coverage>
        )
        target_link_libraries(${_target} PRIVATE
            -pthread 
			-lstdc++fs
        )
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:-D_DEBUG=1>
            $<$<CONFIG:Release>:-D_DEBUG=0>
        )
		
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
	
		target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:-D_DEBUG=1>
            $<$<CONFIG:Release>:-D_DEBUG=0>
        )
    
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:/MTd /Od /Ob0 /Zi /RTC1 /DDEBUG /D_DEBUG /bigobj>
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

