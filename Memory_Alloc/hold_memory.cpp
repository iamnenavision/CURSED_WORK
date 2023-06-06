#include "hold_memory.h"

void * const hold_memory::allocate_with_guard(size_t request_size) const
{
    memory * allocator = get_outer_allocator();

    try
    {
        auto * allocated_block = allocator == nullptr ? ::operator new(request_size) : allocator->allocate(request_size);

        return allocated_block;
    }
    catch (std::exception const & ex)
    {
        throw memory::memory_exception("Memory allocated error");
    }
}

void hold_memory::deallocate_with_guard(void * target_to_dealloc) const
{
    memory * allocator = get_outer_allocator();

    try
    {
        allocator == nullptr ? ::operator delete(target_to_dealloc) : allocator->deallocate(target_to_dealloc);
    }
    catch (std::exception const & ex)
    {
        throw memory::memory_exception("Memory allocated error");
    }
}