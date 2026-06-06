
function(setup_common_target_flags target)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    target_compile_features(${target} PRIVATE cxx_std_17)

    if(MSVC)
        set(CFLAGS /W4 /WX)
    else()
        set(CFLAGS -Wall -Wextra -Werror)
    endif()

    target_compile_options(${target} PRIVATE ${CFLAGS})

endfunction()