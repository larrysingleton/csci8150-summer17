project(src)

include_directories(components)
include_directories(data_structures)
include_directories(include)

set(SOURCE_FILES
        main.c
        components/level_one_cache_controller.c
        components/level_two_cache_controller.c
        components/memory.c
        components/preloader.c
        components/processor.c
        components/victim_cache.c
        components/write_buffer.c
        data_structures/instruction_cache.c
        include/components.h
        include/data_structures.h
        include/main.h)

add_executable(CSCI8150 ${SOURCE_FILES})