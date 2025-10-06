# This file should be included before `CTest` to setup memory checking

if (ENABLE_ASAN)
    set(MEMORYCHECK_TYPE AddressSanitizer)


elseif (WIN32)
    set(MEMORYCHECK_TYPE DrMemory)

    find_program(MEMORYCHECK_COMMAND drmemory)

    set(MEMORYCHECK_COMMAND_OPTIONS "-batch -leaks_only -logdir ${CMAKE_BINARY_DIR}/logs/DrMemory")


elseif (APPLE)
    set(MEMORYCHECK_TYPE leaks)

    find_program(MEMORYCHECK_COMMAND leaks)
    set(MEMORYCHECK_COMMAND MallocStackLogging=1 ${MEMORYCHECK_COMMAND})

    set(MEMORYCHECK_COMMAND_OPTIONS "-atExit")


else()
    set(MEMORYCHECK_TYPE valgrind)

    find_program(MEMORYCHECK_COMMAND valgrind)

    set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all --track-origins=yes --")

endif()


set(CTEST_MEMORYCHECK_TYPE ${MEMORYCHECK_TYPE})
set(CTEST_MEMORYCHECK_COMMAND ${MEMORYCHECK_COMMAND})
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS ${MEMORYCHECK_COMMAND_OPTIONS})
