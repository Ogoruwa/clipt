cmake_minimum_required(VERSION 3.31)

project(CLipt
    VERSION 0.1.0
    LANGUAGES C
    DESCRIPTION "A simple scripting Language, written in C"
)


# Options
option(BUILD_INTERPRETER "Build the interpreter" ON)
option(CLANG_TIDY_WARNINGS_AS_ERRORS "Make cLang tidy warnings errors" OFF)
option(ENABLE_ASAN "Enable address sanitizer" OFF)
option(ENABLE_CLANG_TIDY "Enable cLang-tidy checks" OFF)


# Variables
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
    set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY};--checks=.clang-tidy;-p=build")

    if(CLANG_TIDY_WARNINGS_AS_ERRORS)
        set(CMAKE_C_CLANG_TIDY "${CMAKE_C_CLANG_TIDY};--warnings-as-errors=*")
    endif()
endif()


# Targets
add_subdirectory("src")

add_subdirectory("src/language")

if(BUILD_INTERPRETER)
    add_subdirectory("src/interpreter")
endif()


# Compiler options
if (MSVC)
    target_compile_options(Lang PUBLIC /permissive-)

    if (CLANG_TIDY_WARNINGS_AS_ERRORS)
        target_compile_options(Lang PUBLIC /WX)
        target_link_options(Lang PUBLIC /WX)
    endif()

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        target_link_options(Lang PUBLIC /DEBUG)

        if (ENABLE_ASAN)
            target_compile_options(Lang PUBLIC /fsanitize=address)
        endif()
    endif()

else()
    target_compile_options(Lang PUBLIC -g PUBLIC -free PUBLIC -Wall)

    if (ENABLE_ASAN AND (CMAKE_BUILD_TYPE MATCHES "Debug"))
        target_compile_options(Lang PUBLIC -fsanitize=address,undefined PUBLIC -fno-omit-frame-pointer)
        target_link_options(Lang PUBLIC -fsanitize=address,undefined)
    endif()
endif()



# Testing
include(CTest)

if(BUILD_TESTING)
    add_subdirectory("tests")
endif()


# Packaging
add_subdirectory("package")
