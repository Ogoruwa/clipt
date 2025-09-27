# Configuration for external dependencies
include(FetchContent)


# Hashmap
FetchContent_Declare(hashmap_c
    GIT_REPOSITORY https://github.com/tidwall/hashmap.c.git
    GIT_TAG        5e475b4662622c51b8f375e7b2013e25f3c77b57  # v0.8.1
    FIND_PACKAGE_ARGS ""
)
FetchContent_MakeAvailable(hashmap_c)

add_library(Hashmap SHARED "${hashmap_c_SOURCE_DIR}/hashmap.c")
target_include_directories(Hashmap PUBLIC "${hashmap_c_SOURCE_DIR}")
set_source_files_properties("${hashmap_c_SOURCE_DIR}/hashmap.c" PROPERTIES SKIP_LINTING ON)


# Install
install(TARGETS Hashmap
    RUNTIME DESTINATION lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
