cmake_minimum_required(VERSION 3.31)

project(CLipt
    VERSION 0.1.0
    LANGUAGES C
    DESCRIPTION "A simple scripting Language, written in C"
)


# Options
option(BUILD_INTERPRETER "Build the interpreter" ON)
option(CLANG_TIDY_WARNINGS_AS_ERRORS "Treat clang-tidy warnings as errors" OFF)
option(ENABLE_ASAN "Enable address sanitizer" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy checks" OFF)
option(GENERATE_CTEST_SCRIPT "Generate CTest script for CDash integration" OFF)


# Variables
set(CTEST_USE_LAUNCHERS TRUE)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY NAMES clang-tidy REQUIRED)
    set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY}" "--checks" ".clang-tidy" "-p" "build")

    if(CLANG_TIDY_WARNINGS_AS_ERRORS)
        set(CMAKE_C_CLANG_TIDY "${CMAKE_C_CLANG_TIDY}" "--warnings-as-errors" "*")
    endif()
endif()


# Put this here so it is included no matter what happens
include(CTest)


# Generate CTest script and exit
# Generating the script this way to make use of CMake variables and avoid duplicate configuration
# And to log all the steps in the CDash upload
if (GENERATE_CTEST_SCRIPT)
    set(MY_CTEST_SCRIPT_PATH "${CMAKE_BINARY_DIR}/CTestScript.cmake")
    message(NOTICE "Generating CTest script")

    include(src/MemoryCheck.cmake)
    include(src/GetCommandLineVariables.cmake)

    configure_file("src/CTestScript.cmake" "${MY_CTEST_SCRIPT_PATH}" @ONLY)
    return()
endif()



# Targets
add_subdirectory("src")



# Testing
if(BUILD_TESTING)
    add_subdirectory("tests")
endif()


# Packaging
add_subdirectory("package")
