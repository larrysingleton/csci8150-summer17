cmake_minimum_required(VERSION 3.7)
project(CSCI8150)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/main.c
        src/components/memory.c
        src/components/processor.c
        src/components/level_one_cache_controller.c
        src/components/level_two_cache_controller.c
        src/components/write_buffer.c
        src/components/victim_cache.c
        src/components/preloader.c
        src/include/components.h
        src/data_structures/instruction_cache.c
        src/include/main.h
        src/include/data_structures.h)

include_directories(src/include)

add_executable(CSCI8150 ${SOURCE_FILES})