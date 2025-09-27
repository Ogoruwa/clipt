# Targets
add_library(Lang SHARED token.c lexer.c utils.c error.c)



# Properties
set_target_properties(Lang PROPERTIES OUTPUT_NAME clipt)


# Includes
target_include_directories(Lang
    PUBLIC "${CMAKE_SOURCE_DIR}/include"
)


# Linking
target_link_libraries(Lang PUBLIC Hashmap)


# Install
install(TARGETS Lang
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
