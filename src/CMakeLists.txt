project(src)

include_directories(components
                    data_structures
                    include)

set(SOURCE_FILES
        components/level_one_cache_controller_manager.c
        components/level_two_cache_controller_manager.c
        components/memory_manager.c
        components/preloader.c
        components/cpu_manager.c
        components/victim_cache_manager.c
        components/write_buffer_manager.c
        include/components.h
        include/data_structures.h
        include/main.h
        data_structures/register_file.c
        data_structures/instruction_cache.c
        data_structures/level_one_cache.c
        data_structures/memory.c
        data_structures/level_two_cache.c
        data_structures/victim_cache.c
        data_structures/level_one_write_buffer.c
        data_structures/level_two_write_buffer.c
        data_structures/queues/cpu_to_l1c_queue.c
        data_structures/queues/l1d_to_l1c_queue.c
        data_structures/queues/vc_to_l1c_queue.c
        data_structures/queues/l1c_to_cpu_queue.c
        data_structures/queues/l1c_to_l1d_queue.c
        data_structures/queues/l1c_to_vc_queue.c
        data_structures/queues/l1c_to_l1wb_queue.c
        data_structures/queues/l1c_to_l2c_queue.c
        data_structures/queues/l1wb_to_l1c_queue.c
        data_structures/queues/l2c_to_l1c_queue.c
        data_structures/queues/l2c_to_l2d_queue.c
        data_structures/queues/l2c_to_l2wb_queue.c
        data_structures/queues/l2c_to_mem_queue.c
        data_structures/queues/l2d_to_l2c_queue.c
        data_structures/queues/l2wb_to_l2c_queueu.c
        data_structures/queues/mem_to_l2c_queue.c)

add_executable(CSCI8150 ${SOURCE_FILES} main.c)