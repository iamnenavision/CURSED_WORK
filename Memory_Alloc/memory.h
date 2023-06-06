#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include "../logger/logger.h"

class memory
{

public:

    class memory_exception final : public std::exception
    {
    private:

        std::string _msg;

    public:

        const char *what() const noexcept override;

        memory_exception(const std::string &msg);

    };

public:

    enum class allocation_mode
    {
        first_match,
        the_best_match,
        the_worst_match
    };

public:

    virtual void * const allocate(size_t target_size) const = 0;

    virtual void deallocate(void * target_to_dealloc) const = 0;

    virtual ~memory() = default;

public:

    void * const operator +=(size_t target_size);
    void operator -=(void * target_to_dealloc);

protected:

    virtual size_t get_available_block_service_block_size() const;

    virtual size_t get_occupied_block_service_block_size() const;

    virtual size_t get_allocator_service_block_size() const;

    virtual size_t get_allocated_memory_size() const;

    virtual size_t get_available_block_size(void *current_block) const;

    virtual size_t get_occupied_block_size(void *current_block) const;

    virtual size_t get_occupied_block_size_without_service_block(void *current_block) const;

    virtual memory::allocation_mode get_allocation_mode() const;

    virtual void * get_first_available_block() const;

    virtual void** get_first_available_block_ptr() const;

    virtual void * get_first_occupied_block() const;

    virtual void** get_first_occupied_block_ptr() const;

    virtual void * get_next_available_block(void * current_block) const;

    virtual void * get_next_occupied_block(void * current_block) const;

    virtual void * get_previous_occupied_block(void * current_block) const;

    virtual void * get_previous_available_block(void * current_block) const;

    virtual void * get_start_allocated_memory_address() const;

    virtual void * get_end_allocated_memory_address() const;

    virtual void * get_address_relative_to_allocator(void * current_block_address) const;

    virtual bool get_block_status(void * current_block) const;

    virtual void * get_buddies(void * current_block) const;

protected:

    static std::string address_to_string(void const * const address);

    void memory_state_before_deallocation(void * const target_block, logger * logger) const;

};

#endif //MEMORY_H
