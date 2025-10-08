# This is a CTest script to run the full CTest workflow
# Except configuring the project, which should be done before running this script


# Configure variables

set(CTEST_SITE "@SITE@")
set(CTEST_BUILD_NAME "@BUILDNAME@-${CMAKE_HOST_SYSTEM_PROCESSOR}")

set(CTEST_CMAKE_GENERATOR "@CMAKE_GENERATOR@")
set(CTEST_CONFIGURATION_TYPE "@CMAKE_BUILD_TYPE@")

set(CTEST_SOURCE_DIRECTORY "@PROJECT_SOURCE_DIR@")
set(CTEST_BINARY_DIRECTORY "@PROJECT_BINARY_DIR@")

set(CTEST_MEMORYCHECK_TYPE "@MEMORYCHECK_TYPE@")
set(CTEST_MEMORYCHECK_COMMAND "@MEMORYCHECK_COMMAND@")
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "@MEMORYCHECK_COMMAND_OPTIONS@")
set(CTEST_MEMORYCHECK_SUPPRESSIONS_FILE "@MEMORYCHECK_SUPPRESSIONS_FILE@")
set(CTEST_MEMORYCHECK_SANITIZER_OPTIONS "@MEMORYCHECK_SANITIZER_OPTIONS@")

set(CTEST_COVERAGE_COMMAND "@COVERAGE_COMMAND@")
set(CTEST_COVERAGE_EXTRA_FLAGS "@COVERAGE_EXTRA_FLAGS@")

set(CTEST_TIMEOUT "@DART_TESTING_TIMEOUT@")
set(CTEST_SUBMIT_RETRY_DELAY "@CTEST_SUBMIT_RETRY_DELAY@")
set(CTEST_SUBMIT_RETRY_COUNT "@CTEST_SUBMIT_RETRY_COUNT@")

set(MY_CTEST_SCRIPT_PATH @MY_CTEST_SCRIPT_PATH@)
set(MY_CTEST_SCRIPT_PATH_2 "${CTEST_SOURCE_DIRECTORY}/CTestScript.cmake")


# Checks

message(STATUS "CDASH_MODEL is set to: ${CDASH_MODEL}")
if (NOT("${CDASH_MODEL}" MATCHES "^(Experimental|Nightly|Continuous)$"))
    message(FATAL_ERROR "CDASH_MODEL must be set and be one of Experimental, Nightly or Continuous")
endif()




# Cmake workflow

# Copy script to source directory to prevent deletion when emptying build directory
# Build directory is emptied and the project reconfigured to allow capture of configure output for cdash upload
file(COPY_FILE "${MY_CTEST_SCRIPT_PATH}" "${MY_CTEST_SCRIPT_PATH_2}")
ctest_empty_binary_directory("${CTEST_BINARY_DIRECTORY}")


ctest_start(${CDASH_MODEL})


if (CTEST_UPDATE OR (CDASH_MODEL STREQUAL "Nightly"))
    ctest_update()
endif()

message(NOTICE @CMAKE_ARGS@)
message(NOTICE "STRING: @CMAKE_ARGS@")

list(APPEND configure_options
    @CMAKE_ARGS@;
    # Disable script generation explicitly
    -DGENERATE_CTEST_SCRIPT=OFF
)
ctest_configure(OPTIONS "${configure_options}")
return()

ctest_build()



if (DEFINED CTEST_MEMORYCHECK_COMMAND OR DEFINED CTEST_MEMORYCHECK_TYPE)
    ctest_memcheck()
else()
    message(WARNING "Memory checking disabled: neither memory checker command nor type defined")
    ctest_test()
endif()


ctest_coverage()


if(DEFINED ENV{CDASH_TOKEN})
    ctest_submit(
        HTTPHEADER "Authorization: Bearer $ENV{CDASH_TOKEN}"
    )
else()
    message(WARNING "CDASH_TOKEN environment variable not set, cannot submit results")
endif()


# Move script back to build directory
file(COPY_FILE "${MY_CTEST_SCRIPT_PATH_2}" "${MY_CTEST_SCRIPT_PATH}")
file(REMOVE "${MY_CTEST_SCRIPT_PATH_2}")
