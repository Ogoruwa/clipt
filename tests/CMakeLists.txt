set(sources test_lexer.c)
create_test_sourcelist(tests testdriver.c ${sources})

# Targets
add_executable(TestSuite ${tests})
set_target_properties(TestSuite PROPERTIES OUTPUT_NAME test_suite)
target_link_libraries(TestSuite PUBLIC Lang)


# Tests
foreach(test ${sources})
    get_filename_component(testname ${test} NAME_WE)
    add_test(NAME ${testname} COMMAND TestSuite ${testname})
endforeach()
