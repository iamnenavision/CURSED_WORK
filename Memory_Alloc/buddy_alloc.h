#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H
#include "memory.h"
#include "hold_memory.h"
#include "../logger/logger_impl.h"
#include "../logger/builder_impl.h"
#include "../Logger/JSON/json_impl.h"
#include "../logger/log_hold.h"

class buddy_system_allocator :
        public memory,
        public log_hold,
        public hold_memory
{
private:

    void * _allocated_memory;

public:

    void * const allocate(size_t target_size) const override;

    void deallocate(void * target_to_dealloc) const override;

    explicit buddy_system_allocator(
            size_t power_of_2,
            memory::allocation_mode mode = memory::allocation_mode::first_match,
            logger *logger = nullptr,
            memory *outer_allocator = nullptr
    );

    ~buddy_system_allocator() override;

public:

    buddy_system_allocator(buddy_system_allocator const & other) = delete;

    buddy_system_allocator & operator=(buddy_system_allocator const & other) = delete;

    buddy_system_allocator(buddy_system_allocator && other) = delete;

    buddy_system_allocator & operator=(buddy_system_allocator && other) = delete;

protected:

    size_t get_available_block_service_block_size() const override;

    size_t get_occupied_block_service_block_size() const override;

    size_t get_allocator_service_block_size() const override;

    size_t get_allocated_memory_size() const override;

    size_t get_available_block_size(void * current_block) const override;

    size_t get_occupied_block_size(void * current_block) const override;

    size_t get_occupied_block_size_without_service_block(void * current_block) const override;

    void * get_first_available_block() const override;

    void **get_first_available_block_ptr() const override;

    void * get_previous_available_block(void * current_block) const override;

    void * get_next_available_block(void * current_block) const override;

    memory * get_outer_allocator() const override;

    logger * get_logger() const override;

    memory::allocation_mode get_allocation_mode() const override;

    void * get_start_allocated_memory_address() const override;

    void * get_address_relative_to_allocator(void * current_block_address) const override;

    bool get_block_status(void * current_block) const override;

    void * get_buddies(void * current_block) const override;

};


#endif //BUDDY_ALLOCATOR_H
