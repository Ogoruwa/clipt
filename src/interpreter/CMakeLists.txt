project(CLInterpreter VERSION ${CLipt_VERSION})

set(sources main.c repl.c clipti.c)

# Targets
add_executable(Interpreter ${sources})
set_target_properties(Interpreter PROPERTIES OUTPUT_NAME clipti)

target_include_directories(Interpreter PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(Interpreter Lang)

install(TARGETS Interpreter)
