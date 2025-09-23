project(CLInterpreter VERSION ${CLipt_VERSION})


# Targets
add_library(Interpreter STATIC clipti.c)
add_executable(REPL repl.c)

set_target_properties(Interpreter PROPERTIES OUTPUT_NAME clipti)
set_target_properties(REPL PROPERTIES OUTPUT_NAME cliptr)

target_include_directories(Interpreter PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(REPL PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(Interpreter PRIVATE Lang)
target_link_libraries(REPL PRIVATE Lang Interpreter)

install(TARGETS Interpreter REPL
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
