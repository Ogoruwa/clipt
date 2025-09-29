set(sources test_token.c test_lexer.c test_error.c)
set(TEST_DRIVER_NAME testdriver.c)

create_test_sourcelist(tests ${TEST_DRIVER_NAME} ${sources})


# Targets
add_executable(TestSuite ${tests})
set_target_properties(TestSuite PROPERTIES OUTPUT_NAME test_suite)
set_source_files_properties(${TEST_DRIVER_NAME} PROPERTIES SKIP_LINTING ON)
target_link_libraries(TestSuite PRIVATE Lang)


# Tests
foreach(test ${sources})
    get_filename_component(testname ${test} NAME_WE)
    add_test(NAME ${testname} COMMAND TestSuite ${testname})

    if (MSVC)
        string(CONCAT PATH
            "C:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Tools/MSVC/"
            "${CMAKE_VS_PLATFORM_TOOLSET_VERSION}/bin/HostX64/${CMAKE_LIBRARY_ARCHITECTURE};"
            "$ENV{PATH}"
        )
        set_tests_properties(${testname} PROPERTIES ENVIRONMENT "PATH=${PATH}")
        message("\n\nPath is ${PATH}\n")
    endif()
endforeach()
