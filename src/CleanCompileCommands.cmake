# Remove non clang flags from compile_commands.json for clang-tidy

if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Compiler is Clang, skipping compile commands clean")
    return()
endif()

if (MSVC)
    message(STATUS "Compiler is MSVC, skipping compile commands clean")
    return()
endif()

if (NOT ENABLE_CLANG_TIDY)
    message(STATUS "Clang-tidy is not enabled, skipping compile commands clean")
    return()
endif()



# Add unusable flags here
list(APPEND bad_flags
    "-free"
)



set(cc_json "${CMAKE_BINARY_DIR}/compile_commands.json")
set(old_cc_json "${CMAKE_BINARY_DIR}/compile_commands_old.json")



add_custom_command(
    OUTPUT  ${old_cc_json}
    DEPENDS ${cc_json}

    COMMENT "Cleaning ${cc_json}.json for clang-tidy"
    # -D Arguments have to come first to be parsed
    COMMAND cmake -Dbad_flags:list=${bad_flags} -Dcc_json:filepath=${cc_json} -Dold_cc_json:filepath=${old_cc_json} -P ${CMAKE_SOURCE_DIR}/src/CleanCompileCommandsRunner.cmake
    VERBATIM
)


add_custom_target(CleanCompileCommands ALL
    DEPENDS ${old_cc_json}
)
