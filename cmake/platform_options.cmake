
function(set_qx_target_defines _target)
    target_compile_options(${_target} PRIVATE
        $<$<CONFIG:Debug>:          
            /DQX_DEBUG=1 
            /DQX_RELEASE=0 
            /DQX_RELWITHDEBINFO=0 
            /DQX_MINSIZEREL=0 
            /DQX_DEBUG_BUILD=1 
            /DQX_RELEASE_BUILD=0>
            
        $<$<CONFIG:Release>:        
            /DQX_DEBUG=0 
            /DQX_RELEASE=1 
            /DQX_RELWITHDEBINFO=0 
            /DQX_MINSIZEREL=0 
            /DQX_DEBUG_BUILD=0 
            /DQX_RELEASE_BUILD=1>
            
        $<$<CONFIG:RelWithDebInfo>: 
            /DQX_DEBUG=0 
            /DQX_RELEASE=0 
            /DQX_RELWITHDEBINFO=1 
            /DQX_MINSIZEREL=0 
            /DQX_DEBUG_BUILD=1 
            /DQX_RELEASE_BUILD=0>
            
        $<$<CONFIG:MinSizeRel>:     
            /DQX_DEBUG=0 
            /DQX_RELEASE=0 
            /DQX_RELWITHDEBINFO=0 
            /DQX_MINSIZEREL=1 
            /DQX_DEBUG_BUILD=0 
            /DQX_RELEASE_BUILD=1>
            
            
        $<$<PLATFORM_ID:Windows>:
            /DQX_WIN=1
            /DQX_MACOS=0
            /DQX_LINUX=0>
            
        $<$<PLATFORM_ID:Darwin>:
            /DQX_WIN=0
            /DQX_MACOS=1
            /DQX_LINUX=0>
            
        $<$<PLATFORM_ID:Linux>:
            /DQX_WIN=0
            /DQX_MACOS=0
            /DQX_LINUX=1>
    )
endfunction()

function(set_qxlib_target_options _target)

    set_qx_target_defines(${_target})

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    
        target_link_libraries(${_target} PRIVATE
            -pthread
        )
        
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)    
        
        target_compile_options(${_target} PRIVATE
            $<$<CONFIG:Debug>:--coverage -O0 -g>
        )
        target_link_options(${_target} PRIVATE 
            $<$<CONFIG:Debug>:--coverage>
        )
        target_link_libraries(${_target} PRIVATE
            -pthread
        )
    
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Intel)
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

