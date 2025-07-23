cmake_minimum_required(VERSION 3.30.0)

# Project Info

project(CLipt VERSION 0.1.0)


# Variables

set(CMAKE_C_STANDARD_REQUIRED True)
set(TARGET_SYSTEM ${CMAKE_SYSTEM_NAME})
set(HOST_SYSTEM ${CMAKE_HOST_SYSTEM_NAME})

option(ENABLE_PACKING "Enable packing using cpack" OFF)
option(ENABLE_TESTING "Enable testing using ctest" OFF)

option(BUILD_INTERPRETER "Build the interpreter" ON)


# Targets

if(BUILD_INTERPRETER)
    add_subdirectory("src/clipt/interpreter/")
endif()


# Packing

if(ENABLE_PACKING)
    include(InstallRequiredSystemLibraries)
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
    set(CPACK_PACKAGE_VERSION_MAJOR "${SocketServer_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${SocketServer_VERSION_MINOR}")
    set(CPACK_SOURCE_GENERATOR "TGZ")
    include(CPack)
endif()


# Testing

if(ENABLE_TESTING)
    enable_testing()
    include(CTest)

    function(do_test target arg result)
        add_test(NAME Comp${arg} COMMAND ${target} ${arg})
        set_tests_properties(Comp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
    endfunction()

    do_test(0 0 0)
endif()
