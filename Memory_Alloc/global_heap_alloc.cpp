#include "global_heap_alloc.h"

global_heap_alloc::global_heap_alloc(logger * const log_memory)
    : _log_memory(log_memory) {}

void * global_heap_alloc::get_address_relative_to_allocator(void * current_block_address) const
{
    return current_block_address;
}

logger * global_heap_alloc::get_logger() const
{
    return _log_memory;
}

memory * global_heap_alloc::get_outer_allocator() const
{
    return nullptr;
}

size_t global_heap_alloc::get_occupied_block_size_without_service_block(void *current_block) const
{
    return *(reinterpret_cast<size_t*>(current_block) - 1);
}

void * const global_heap_alloc::allocate(size_t target_size) const
{
    try
    {
        auto *block_of_memory = ::operator new(target_size + sizeof(size_t));

        auto *block_size = reinterpret_cast<size_t*>(block_of_memory);
        *block_size = target_size;


        this->trace_with_guard("[GLOBAL HEAP ALLOCATOR] Memory allocated success at address: " + address_to_string(block_size + 1) + " success.");

        return reinterpret_cast<void*>(block_size + 1);
    }
    catch (const std::bad_alloc &ex)
    {
        std::string message = "Memory allocated error";
        warning_with_guard("[GLOBAL HEAP ALLOCATOR] " + message + ".");

        throw memory_exception("Memory allocated error");
    }
}

void global_heap_alloc::deallocate(void * target_to_dealloc) const
{
    memory_state_before_deallocation(target_to_dealloc, get_logger());

    auto * target_block = reinterpret_cast<void*>(reinterpret_cast<size_t*>(target_to_dealloc) - 1);

    ::operator delete(target_block);

    this->trace_with_guard("[GLOBAL HEAP ALLOCATOR] Memory at address: " + address_to_string(target_to_dealloc) + " was deallocated.");
}