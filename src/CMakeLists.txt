include("HashMap.cmake")

add_subdirectory("language")

if(BUILD_INTERPRETER)
    add_subdirectory("interpreter")
endif()


include("CompilerOptions.cmake")

include("ClangTidy.cmake")

if (TARGET CleanCompileCommands)
    add_dependencies(Lang CleanCompileCommands)
endif()
