
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

        string(REGEX REPLACE "bin/.+" "include" MSVC_INCLUDE_PATH ${CMAKE_CXX_COMPILER})
    
        target_compile_options(${_target} PRIVATE
            # exceptions support
            /EHsc 
            # enable all warnings and treat them as errors
            /Wall /WX
            # ignore all MSVC headers warnings
            /external:I"${MSVC_INCLUDE_PATH}" /external:W0
            # ignore trash or too pedantic warnings
            /wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
            /wd4062 # enumerator 'identifier' in switch of enum 'enumeration' is not handled
            /wd4100 # 'identifier' : unreferenced formal parameter
            /wd4355 # 'this' : used in base member initializer list
            /wd4365 # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch: MVSC headers warnings
            /wd4514 # 'function' : unreferenced inline function has been removed
            /wd4599 # 'flag path': command line argument number number does not match precompiled header: conflict with /external:I path which leads to the broken "edit and continue"
            /wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
            /wd4625 # 'type': move assignment operator was implicitly defined as deleted
            /wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
            /wd4710 # 'function' : function not inlined
            /wd4711 # 'function' selected for inline expansion. Inlining is performed at the compiler's discretion
            /wd4820 # 'bytes' bytes padding added after construct 'member_name'
            /wd4868 # 'file(line_number)' compiler may not enforce left-to-right evaluation order in braced initializer list
            /wd5026 # 'type': move constructor was implicitly defined as deleted
            /wd5027 # 'type': move assignment operator was implicitly defined as deleted
            /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
            /wd5246 # 'member': the initialization of a subobject should be wrapped in braces
            /wd5262 # 'implicit fall-through occurs here; are you missing a break statement? Use [[fallthrough]] when a break statement is intentionally omitted between cases
            /wd5264 # 'variable-name': 'const' variable is not used
            
            $<$<CONFIG:Debug>:          /MTd /ZI /D_DEBUG>
            $<$<CONFIG:Release>:        /MT /DNDEBUG>
            $<$<CONFIG:RelWithDebInfo>: /MT /DNDEBUG>
            $<$<CONFIG:MinSizeRel>:     /MT /DNDEBUG>

            /MP # multithreaded compilation
        )
        
        target_link_options(${_target} PRIVATE 
            $<$<CONFIG:Release>: /NODEFAULTLIB:LIBCMTD>
            $<$<CONFIG:Debug>: /INCREMENTAL>
            "/ignore:4098" # defaultlib 'library' conflicts with use of other libs; use /NODEFAULTLIB:library
            "/ignore:4099" # PDB 'filename' was not found with 'object/library' or at 'path'; linking object as if no debug info
        )
        
    endif()

    target_compile_definitions(${_target} PRIVATE
        $<$<CONFIG:Debug>:          QX_DEBUG=1 QX_RELEASE=0 QX_REL_WITH_DEBUG_INFO=0 QX_MIN_SIZE_RELEASE=0>
        $<$<CONFIG:Release>:        QX_DEBUG=0 QX_RELEASE=1 QX_REL_WITH_DEBUG_INFO=0 QX_MIN_SIZE_RELEASE=0>
        $<$<CONFIG:RelWithDebInfo>: QX_DEBUG=0 QX_RELEASE=0 QX_REL_WITH_DEBUG_INFO=1 QX_MIN_SIZE_RELEASE=0>
        $<$<CONFIG:MinSizeRel>:     QX_DEBUG=0 QX_RELEASE=0 QX_REL_WITH_DEBUG_INFO=0 QX_MIN_SIZE_RELEASE=1>
    )
        
    target_compile_features(${_target} PRIVATE 
        cxx_std_20
    )
    
    set_target_properties(${_target} PROPERTIES 
        LINKER_LANGUAGE CXX
    )
        
endfunction()

