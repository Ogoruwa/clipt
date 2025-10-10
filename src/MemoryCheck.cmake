# This file should be included before `CTest` to setup memory checking

if (ENABLE_ASAN)
    set(MEMORYCHECK_TYPE AddressSanitizer)

    set(MEMORYCHECK_COMMAND "")

    set(MEMORYCHECK_SANITIZER_OPTIONS "verbosity=1:symbolize=1:abort_on_error=0:detect_leaks=1")


elseif (WIN32)
    # TODO: Support Dr. Memory on Windows properly
    set(MEMORYCHECK_TYPE DrMemory)

    find_program(MEMORYCHECK_COMMAND drmemory)

    set(MEMORYCHECK_COMMAND_OPTIONS "-batch -leaks_only -logdir ${CMAKE_BINARY_DIR}/logs/DrMemory")


elseif (APPLE)
    # TODO: Support leaks on macOS properly
    set(MEMORYCHECK_TYPE leaks)

    find_program(MEMORYCHECK_COMMAND leaks)
    set(MEMORYCHECK_COMMAND MallocStackLogging=1 ${MEMORYCHECK_COMMAND})

    set(MEMORYCHECK_COMMAND_OPTIONS "-atExit")


else()
    set(MEMORYCHECK_TYPE valgrind)

    find_program(MEMORYCHECK_COMMAND valgrind)

    set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all --track-origins=yes --")

endif()
