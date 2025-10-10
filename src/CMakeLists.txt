include("HashMap.cmake")

add_subdirectory("language")

if(BUILD_INTERPRETER)
    add_subdirectory("interpreter")
endif()


include("MemoryCheck.cmake")

include("CompilerOptions.cmake")

include("CleanCompileCommands.cmake")

if (TARGET CleanCompileCommands)
    add_dependencies(Lang CleanCompileCommands)
endif()
