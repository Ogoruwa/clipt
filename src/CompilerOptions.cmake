# Compiler options

if (MSVC)
    target_compile_options(Lang PUBLIC /permissive-)

    if (CLANG_TIDY_WARNINGS_AS_ERRORS)
        target_compile_options(Lang PUBLIC /WX)
        target_link_options(Lang PUBLIC /WX)
    endif()

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        target_link_options(Lang PUBLIC /DEBUG)

        if (ENABLE_ASAN)
            target_compile_options(Lang PUBLIC /fsanitize=address)
        endif()
    endif()



elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Lang PUBLIC -free)

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        if(ENABLE_ASAN)
            target_compile_options(Lang PUBLIC -fsanitize=address,undefined PUBLIC -fno-omit-frame-pointer)
            target_link_options(Lang PUBLIC -fsanitize=address,undefined)
        endif()
    endif()



elseif(CMAKE_C_COMPILER_ID STREQUAL "CLANG")

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        if(ENABLE_ASAN)
            target_compile_options(Lang PUBLIC -fsanitize=address,undefined PUBLIC -fno-omit-frame-pointer)
            target_link_options(Lang PUBLIC -fsanitize=address,undefined)
        endif()
    endif()

endif()
