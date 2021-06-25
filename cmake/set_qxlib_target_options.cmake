
function(set_qxlib_target_options _target)

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    
        target_link_libraries(${_target} PRIVATE
            -pthread 
            -lstdc++fs
        )
        
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
        
        target_link_options(${_target} PRIVATE 
            $<$<CONFIG:Debug>:--coverage>
        )
        
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:--coverage>
        )
        
        target_link_libraries(${_target} PRIVATE
            -pthread 
			-lstdc++fs
        )
		
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
    
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    
        target_compile_options(${_target} PRIVATE
            /bigobj
        )

    endif()
            
    target_link_libraries(${_target} PRIVATE
        ${GTEST_LIBRARIES}
    )
    
endfunction()

