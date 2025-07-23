project(CLiptInterpreter VERSION ${CLipt_VERSION})


# Targets

add_executable(clipti main.c)

target_include_directories(clipti PUBLIC "${PROJECT_BINARY_DIR}")
