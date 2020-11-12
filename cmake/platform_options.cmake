
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
            /EHsc /Wall /WX
            /wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
            /wd4514 # 'function' : unreferenced inline function has been removed
            /wd4625 # 'type': move assignment operator was implicitly defined as deleted
            /wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
            /wd4710 # 'function' : function not inlined
            /wd4820 # 'bytes' bytes padding added after construct 'member_name'
            /wd5026 # 'type': move constructor was implicitly defined as deleted
            /wd5027 # 'type': move assignment operator was implicitly defined as deleted
            /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
            
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

