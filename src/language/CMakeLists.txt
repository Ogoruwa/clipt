# Targets
add_library(Lang SHARED token.c lexer.c utils.c error.c)


# External Targets
include(FetchContent)

FetchContent_Declare(hashmap_c
    GIT_REPOSITORY https://github.com/tidwall/hashmap.c.git
    GIT_TAG        5e475b4662622c51b8f375e7b2013e25f3c77b57  # v0.8.1
    FIND_PACKAGE_ARGS ""
)
FetchContent_MakeAvailable(hashmap_c)
target_sources(Lang PUBLIC "${hashmap_c_SOURCE_DIR}/hashmap.c")


# Properties
set_target_properties(Lang PROPERTIES OUTPUT_NAME clipt)


# Includes
target_include_directories(Lang
    PUBLIC "${CMAKE_SOURCE_DIR}/include"
    PUBLIC "${hashmap_c_SOURCE_DIR}"
)


# Install
install(TARGETS Lang
    RUNTIME DESTINATION lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
