set(sources token.c lexer.c utils.c error.c)

# Targets
add_library(Lang SHARED ${sources})
set_target_properties(Lang PROPERTIES OUTPUT_NAME clipt)

target_include_directories(Lang PUBLIC "${CMAKE_SOURCE_DIR}/include")

install(TARGETS Lang)
