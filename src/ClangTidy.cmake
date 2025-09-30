# Remove non clang flags from compile_commands.json for clang-tidy

if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Skipping compile commands cleaning since the compiler is Clang")
    return()
endif()

if (NOT ENABLE_CLANG_TIDY)
    message(STATUS "Skipping compile commands cleaning since clang-tidy is not enabled")
    return()
endif()


list(APPEND bad_flags
    "-free"
)

list(JOIN bad_flags "|" bad_flags_string)


set(cc_json "${CMAKE_BINARY_DIR}/compile_commands.json")
set(old_cc_json "${CMAKE_BINARY_DIR}/compile_commands_old.json")


add_custom_command(
    OUTPUT  ${old_cc_json}
    DEPENDS ${cc_json}

    COMMAND ${CMAKE_COMMAND} -E copy "${cc_json}" "${old_cc_json}"
    COMMAND sed -E "\"s/( )(${bad_flags_string})( )/ /g\"" < "${old_cc_json}" > "${cc_json}"
)

add_custom_target(CleanCompileCommands ALL
    DEPENDS ${old_cc_json}
)
