#ifndef GLOBAL_HEAP_MEMORY_H
#define GLOBAL_HEAP_MEMORY_H
#include "memory.h"
#include "hold_memory.h"
#include "../logger/logger_impl.h"
#include "../logger/builder_impl.h"
#include "../Logger/JSON/json_impl.h"
#include "../logger/log_hold.h"

class global_heap_alloc final :
        public memory,
        public log_hold,
        public hold_memory
{
private:

    logger *_log_memory = nullptr;

public:

    void * const allocate(size_t target_size) const override;

    void deallocate(void * target_to_dealloc) const override;

    global_heap_alloc(logger * const log_memory = nullptr);

public:

    global_heap_alloc(global_heap_alloc const & other) = delete;

    global_heap_alloc & operator=(global_heap_alloc const & other) = delete;

    global_heap_alloc(global_heap_alloc && other) = delete;

    global_heap_alloc & operator=(global_heap_alloc && other) = delete;

protected:

    size_t get_occupied_block_size_without_service_block(void *current_block) const override;

    void * get_address_relative_to_allocator(void * current_block_address) const override;

    logger * get_logger() const override;

    memory * get_outer_allocator() const override;
};


#endif //GLOBAL_HEAP_MEMORY_H
