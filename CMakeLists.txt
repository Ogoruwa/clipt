cmake_minimum_required(VERSION 3.31)

project(CLipt VERSION 0.1.0)

# Variables
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")

option(BUILD_INTERPRETER "Build the interpreter" ON)


# Targets
add_subdirectory("src/language")

if(BUILD_INTERPRETER)
    add_subdirectory("src/interpreter")
endif()


# Testing
include(CTest)

if(BUILD_TESTING)
    add_subdirectory("tests")
endif()


# Packaging
add_subdirectory("package")
