if (NOT EXISTS ${cc_json})
    message(FATAL_ERROR "Compile commands file `${cc_json}` does not exist")
endif()


list(JOIN bad_flags "|" bad_flags)

message(STATUS "Removing flags matching regex: ${bad_flags}")

file(COPY_FILE ${cc_json} ${old_cc_json})
file(READ ${cc_json} FILE_CONTENTS)

string(REGEX REPLACE " (${bad_flags}) " " " FILE_CONTENTS ${FILE_CONTENTS})
file(WRITE ${cc_json} ${FILE_CONTENTS})
