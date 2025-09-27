project(CLInterpreter
    VERSION ${CLipt_VERSION}
    DESCRIPTION "Interpreter for CLipt language"
)


# Targets
set(sources clipti.c)
add_library(Interpreter STATIC ${sources})

set(sources repl.c)
add_executable(REPL ${sources})


# Properties
set_target_properties(Interpreter PROPERTIES OUTPUT_NAME clipti)
set_target_properties(REPL PROPERTIES OUTPUT_NAME cliptr)


# Includes
target_include_directories(Interpreter PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(REPL PRIVATE "${CMAKE_SOURCE_DIR}/include")


# Linking
target_link_libraries(Interpreter PRIVATE Lang)
target_link_libraries(REPL PRIVATE Lang Interpreter)


# Install
install(TARGETS Interpreter REPL
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
