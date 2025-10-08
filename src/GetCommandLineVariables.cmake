# Collect all command line specified variables to pass to the configure step in the ctest script
# Author: Timothy Wrona
# Source: https://cmake.org/pipermail/cmake/2019-April/069336.html


get_cmake_property(CACHE_VARS CACHE_VARIABLES)

foreach(CACHE_VAR ${CACHE_VARS})

    get_property(CACHE_VAR_HELPSTRING CACHE ${CACHE_VAR} PROPERTY HELPSTRING)

    if(CACHE_VAR_HELPSTRING STREQUAL "No help, variable specified on the command line.")
        get_property(CACHE_VAR_TYPE CACHE ${CACHE_VAR} PROPERTY TYPE)

        if(CACHE_VAR_TYPE STREQUAL "UNINITIALIZED")
            set(CACHE_VAR_TYPE)
        else()
            set(CACHE_VAR_TYPE :${CACHE_VAR_TYPE})
        endif()

        # #
        if(${${CACHE_VAR}} STREQUAL "")
            set(CACHE_VAR_VALUE "\"\"")
        else()
            set(CACHE_VAR_VALUE "${${CACHE_VAR}}")
        endif()

        if(CACHE_VAR_TYPE STREQUAL ":FILEPATH")
            string(REPLACE " " "\\\ " CACHE_VAR_VALUE "${CACHE_VAR_VALUE}")
            set(CACHE_VAR_VALUE "\'${CACHE_VAR_VALUE}\'")
        endif()
        # #

        list(APPEND CMAKE_ARGS "-D${CACHE_VAR}${CACHE_VAR_TYPE}=${CACHE_VAR_VALUE}")
    endif()

endforeach()
