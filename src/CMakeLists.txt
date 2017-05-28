project(src)

include_directories(components
                    data_structures
                    include)

set(SOURCE_FILES
        components/level_one_cache_controller.c
        components/level_two_cache_controller.c
        components/memory.c
        components/preloader.c
        components/processor.c
        components/victim_cache.c
        components/write_buffer.c
        include/components.h
        include/data_structures.h
        include/main.h
        data_structures/instruction_cache.c)

add_executable(CSCI8150 ${SOURCE_FILES} main.c)
add_executable(unit-tests ${SOURCE_FILES} unit-tests/instruction-cache-test.c)