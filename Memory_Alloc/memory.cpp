#include "memory.h"
#include <sstream>

void * const memory::operator+=(size_t target_size)
{
    return allocate(target_size);
}

void memory::operator-=(void * target_to_dealloc)
{
    deallocate(target_to_dealloc);
}

memory::memory_exception::memory_exception(const std::string &msg)
    : _msg(msg) {}

const char *memory::memory_exception::what() const noexcept
{
    return _msg.c_str();
}

std::string memory::address_to_string(const void * const address)
{
    return std::string { (std::stringstream () << address).str() };
}

size_t memory::get_available_block_service_block_size() const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_occupied_block_service_block_size() const
{
    throw memory::memory_exception("Method not implemented");
}
size_t memory::get_allocator_service_block_size() const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_allocated_memory_size() const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_available_block_size(void * current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_occupied_block_size(void * current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_occupied_block_size_without_service_block(void *current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

memory::allocation_mode memory::get_allocation_mode() const
{
    throw memory::memory_exception("Method not implemented");
}

void* memory::get_first_available_block() const
{
    throw memory::memory_exception("Method not implemented");
}

void** memory::get_first_available_block_ptr() const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_first_occupied_block() const
{
    throw memory::memory_exception("Method not implemented");
}

void** memory::get_first_occupied_block_ptr() const
{
    throw memory::memory_exception("Method not implemented");
}

void* memory::get_next_available_block(void *current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_next_occupied_block(void * current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_previous_occupied_block(void * current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_start_allocated_memory_address() const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_end_allocated_memory_address() const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_address_relative_to_allocator(void * current_block_address) const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_previous_available_block(void * current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

bool memory::get_block_status(void * current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

void * memory::get_buddies(void * current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

void memory::memory_state_before_deallocation(void * const block_of_memory, logger * log) const
{
    if (log == nullptr)
    {
        return;
    }

    auto block_size = get_occupied_block_size_without_service_block(block_of_memory);
    auto * iter = reinterpret_cast<unsigned char*>(block_of_memory);

    std::string bytes;

    for(size_t i = 0; i < block_size; i++)
    {
        bytes += std::to_string(static_cast<unsigned short>(*iter++));

        if (i != block_size - 1)
        {
            bytes += ' ';
        }
    }

    auto * block_of_memory_address = get_address_relative_to_allocator(block_of_memory);

    std::string address = address_to_string(block_of_memory_address);


    log->log("Memory state at address: " + address + " = [" + bytes + "]", logger::severity::trace);

}