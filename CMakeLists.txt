cmake_minimum_required(VERSION 3.24)
project(kursovaya)

set(CMAKE_CXX_STANDARD 20)

add_executable(kursovaya
        main.cpp
        Logger/builder_impl.cpp
        Logger/logger_impl.cpp
        Logger/JSON/json_impl.cpp
        Logger/log_hold.cpp
        Memory_Alloc/memory.cpp
        Memory_Alloc/global_heap_alloc.cpp
        Memory_Alloc/sorted_list_alloc.cpp
        Memory_Alloc/border_descriptors_alloc.cpp
        Memory_Alloc/buddy_alloc.cpp
        Memory_Alloc/hold_memory.cpp
        Trees/associative_container.h
        Trees/binary_search_tree.h
        Trees/splay_tree.h
        Comparators/compare_strings.cpp
        Comparators/compare_keys.cpp
        Data_structures/data_collection.cpp
        Data_structures/scheme.cpp
        Data_structures/pool.cpp
        Data_structures/database.cpp
        Data_Types/data_type.h
        Data_Types/allocator_types.h
        Request_Handler/command_add_collection.cpp
        Request_Handler/command_add_data.cpp
        Request_Handler/command_add_pool.cpp
        Request_Handler/command_add_scheme.cpp
        Request_Handler/command_get_data.cpp
        Request_Handler/command_get_data_between.cpp
        Request_Handler/command_remove_collection.cpp
        Request_Handler/command_remove_data.cpp
        Request_Handler/command_remove_pool.cpp
        Request_Handler/command_remove_scheme.cpp
        Request_Handler/command_update_data.cpp
        Request_Handler/handler.h
        Request_Handler/request_handler_with_command.cpp
        Request_Handler/request_handler_with_command_chain.cpp
        Request_Handler/command.cpp)
