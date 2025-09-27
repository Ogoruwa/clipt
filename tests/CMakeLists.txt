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

    if (WIN32)
        set_tests_properties(${testname} PROPERTIES
            ENVIRONMENT "PATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}\\;$ENV{PATH}"
        )
    endif()
endforeach()
