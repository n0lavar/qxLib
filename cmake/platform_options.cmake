
function(set_qx_target_defines _target)
    
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang 
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang
    )
        set (DEFINE_PREFIX "-D")
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        set (DEFINE_PREFIX "/D")
    endif()

    target_compile_options(${_target} PRIVATE
        $<$<CONFIG:Debug>:          
            ${DEFINE_PREFIX}QX_DEBUG=1 
            ${DEFINE_PREFIX}QX_RELEASE=0 
            ${DEFINE_PREFIX}QX_RELWITHDEBINFO=0 
            ${DEFINE_PREFIX}QX_MINSIZEREL=0 
            ${DEFINE_PREFIX}QX_DEBUG_BUILD=1 
            ${DEFINE_PREFIX}QX_RELEASE_BUILD=0>
            
        $<$<CONFIG:Release>:        
            ${DEFINE_PREFIX}QX_DEBUG=0 
            ${DEFINE_PREFIX}QX_RELEASE=1 
            ${DEFINE_PREFIX}QX_RELWITHDEBINFO=0 
            ${DEFINE_PREFIX}QX_MINSIZEREL=0 
            ${DEFINE_PREFIX}QX_DEBUG_BUILD=0 
            ${DEFINE_PREFIX}QX_RELEASE_BUILD=1>
            
        $<$<CONFIG:RelWithDebInfo>: 
            ${DEFINE_PREFIX}QX_DEBUG=0 
            ${DEFINE_PREFIX}QX_RELEASE=0 
            ${DEFINE_PREFIX}QX_RELWITHDEBINFO=1 
            ${DEFINE_PREFIX}QX_MINSIZEREL=0 
            ${DEFINE_PREFIX}QX_DEBUG_BUILD=1 
            ${DEFINE_PREFIX}QX_RELEASE_BUILD=0>
            
        $<$<CONFIG:MinSizeRel>:     
            ${DEFINE_PREFIX}QX_DEBUG=0 
            ${DEFINE_PREFIX}QX_RELEASE=0 
            ${DEFINE_PREFIX}QX_RELWITHDEBINFO=0 
            ${DEFINE_PREFIX}QX_MINSIZEREL=1 
            ${DEFINE_PREFIX}QX_DEBUG_BUILD=0 
            ${DEFINE_PREFIX}QX_RELEASE_BUILD=1>
            
            
        $<$<PLATFORM_ID:Windows>:
            ${DEFINE_PREFIX}QX_WIN=1
            ${DEFINE_PREFIX}QX_MACOS=0
            ${DEFINE_PREFIX}QX_LINUX=0>
            
        $<$<PLATFORM_ID:Darwin>:
            ${DEFINE_PREFIX}QX_WIN=0
            ${DEFINE_PREFIX}QX_MACOS=1
            ${DEFINE_PREFIX}QX_LINUX=0>
            
        $<$<PLATFORM_ID:Linux>:
            ${DEFINE_PREFIX}QX_WIN=0
            ${DEFINE_PREFIX}QX_MACOS=0
            ${DEFINE_PREFIX}QX_LINUX=1>
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

