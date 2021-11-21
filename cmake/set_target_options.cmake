
function(set_target_options _target)

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:-D_DEBUG>
        )
        
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
        
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:-D_DEBUG>
        )
		
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
	
		target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:-D_DEBUG>
        )
    
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    
        target_compile_options(${_target} PRIVATE
            /EHsc /Wall /WX
            /wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
            /wd4062 # enumerator 'identifier' in switch of enum 'enumeration' is not handled
            /wd4100 # 'identifier' : unreferenced formal parameter
            /wd4355 # 'this' : used in base member initializer list
            /wd4365 # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch: MVSC headers warnings
            /wd4514 # 'function' : unreferenced inline function has been removed
            /wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
            /wd4625 # 'type': move assignment operator was implicitly defined as deleted
            /wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
            /wd4710 # 'function' : function not inlined
            /wd4711 # 'function' selected for inline expansion. Inlining is performed at the compiler's discretion
            /wd4820 # 'bytes' bytes padding added after construct 'member_name'
            /wd5026 # 'type': move constructor was implicitly defined as deleted
            /wd5027 # 'type': move assignment operator was implicitly defined as deleted
            /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
            /wd5246 # 'member': the initialization of a subobject should be wrapped in braces
            
            $<$<CONFIG:Debug>:          /MTd /ZI /D_DEBUG>
            $<$<CONFIG:Release>:        /MT /DNDEBUG>
            $<$<CONFIG:RelWithDebInfo>: /MTd /ZI /D_DEBUG>
            $<$<CONFIG:MinSizeRel>:     /MT /DNDEBUG>
        )
        
        target_link_options(${_target} PRIVATE 
            $<$<CONFIG:Release>: /NODEFAULTLIB:LIBCMTD>
            $<$<CONFIG:Debug>: /INCREMENTAL>
        )

        
    endif()
        
    target_compile_features(${_target} PRIVATE 
        cxx_std_20
    )
    
    set_target_properties(${_target} PROPERTIES 
        LINKER_LANGUAGE CXX
    )
        
endfunction()

