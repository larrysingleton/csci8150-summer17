project(src)

include_directories(components
                    data_structures
                    include
                    unit-tests)

set(SOURCE_FILES
        components/level_one_cache_manager.c
        components/level_two_cache_manager.c
        components/memory_manager.c
        components/preloader.c
        components/processor.c
        components/victim_cache_manager.c
        components/write_buffer_manager.c
        include/components.h
        include/data_structures.h
        include/main.h
        data_structures/register_file.c
        data_structures/instruction_cache.c
        data_structures/queue.c
        data_structures/level_one_cache.c
        data_structures/memory.c
        data_structures/level_two_cache.c)

set(TEST_FILES
        unit-tests/instruction-cache-test.c
        unit-tests/register-file-test.c
        unit-tests/test.c
        unit-tests/tests.h
        unit-tests/memory-test.c)

add_executable(CSCI8150 ${SOURCE_FILES} main.c)
add_executable(unit-tests ${SOURCE_FILES} ${TEST_FILES})