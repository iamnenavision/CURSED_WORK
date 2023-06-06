#include "sorted_list_alloc.h"

size_t sorted_list_alloc::get_allocator_service_block_size() const
{
    return sizeof(size_t) + sizeof(memory*) + sizeof(logger*) + sizeof(memory::allocation_mode) + sizeof(void*);
}

size_t sorted_list_alloc::get_allocated_memory_size() const
{
    return *reinterpret_cast<size_t *>(_allocated_memory);
}

memory* sorted_list_alloc::get_outer_allocator() const
{
    return *reinterpret_cast<memory**>(reinterpret_cast<size_t *>(_allocated_memory) + 1);
}

logger * sorted_list_alloc::get_logger() const
{
    return *reinterpret_cast<logger**>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*));
}

memory::allocation_mode sorted_list_alloc::get_allocation_mode() const
{
    return *reinterpret_cast<memory::allocation_mode*>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*) + sizeof(logger*));
}

void* sorted_list_alloc::get_first_available_block() const
{
    return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*) + sizeof(logger*) + sizeof(allocation_mode));
}

void** sorted_list_alloc::get_first_available_block_ptr() const
{
    return reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*) + sizeof(logger*) + sizeof(allocation_mode));
}

void* sorted_list_alloc::get_next_available_block(void * current_block) const
{
    return *reinterpret_cast<void**>(reinterpret_cast<size_t*>(current_block) + 1);
}


size_t sorted_list_alloc::get_available_block_service_block_size() const
{
    return sizeof(size_t) + sizeof(void*);
}

size_t sorted_list_alloc::get_occupied_block_service_block_size() const
{
    return sizeof(size_t);
}

size_t sorted_list_alloc::get_available_block_size(void * current_block) const
{
    return *reinterpret_cast<size_t*>(current_block);
}

size_t sorted_list_alloc::get_occupied_block_size(void * current_block) const
{
    return *(reinterpret_cast<size_t*>(current_block) - 1);
}

size_t sorted_list_alloc::get_occupied_block_size_without_service_block(void * current_block) const
{
    return get_occupied_block_size(current_block) - get_occupied_block_service_block_size();
}

void * sorted_list_alloc::get_start_allocated_memory_address() const
{
    return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(_allocated_memory) + get_allocator_service_block_size());
}

void * sorted_list_alloc::get_address_relative_to_allocator(void * current_block_address) const
{
    return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(current_block_address) - reinterpret_cast<unsigned char*>(get_start_allocated_memory_address()));
}

sorted_list_alloc::sorted_list_alloc(
        size_t target_size,
        memory::allocation_mode mode,
        logger *log,
        memory *outer_allocator
        )
{
    size_t allocator_service_block_size = get_allocator_service_block_size();

    size_t available_block_service_block_size = get_available_block_service_block_size();

    size_t memory_size = allocator_service_block_size + available_block_service_block_size + target_size;

    if (outer_allocator == nullptr)
    {
        _allocated_memory = ::operator new(memory_size);
    }
    else
    {
        _allocated_memory = outer_allocator->allocate(memory_size);
    }

    auto * const allocated_memory_size = reinterpret_cast<size_t*>(_allocated_memory);
    *allocated_memory_size = memory_size;

    auto * const outer_allocator_ptr = reinterpret_cast<memory**>(allocated_memory_size + 1);
    *outer_allocator_ptr = outer_allocator;

    auto * const logger_ptr = reinterpret_cast<logger**>(outer_allocator_ptr + 1);
    *logger_ptr = log;

    auto * const allocation_mode_ptr = reinterpret_cast<memory::allocation_mode*>(logger_ptr + 1);
    *allocation_mode_ptr = mode;

    auto * const first_available_block_ptr = reinterpret_cast<void**>(allocation_mode_ptr + 1);
    *first_available_block_ptr = reinterpret_cast<void*>(first_available_block_ptr + 1);

    auto * const first_available_block_size = reinterpret_cast<size_t*>(*first_available_block_ptr);
    *first_available_block_size = target_size + available_block_service_block_size;

    auto * const next_available_block_ptr = reinterpret_cast<void**>(first_available_block_size + 1);
    *next_available_block_ptr = nullptr;

    this->trace_with_guard("[SORTED LIST ALLOCATOR] Allocator successfully created.");

}

void * const sorted_list_alloc::allocate(size_t request_size) const
{
    if (request_size < sizeof(void*))
    {
        this->trace_with_guard("[SORTED LIST ALLOCATOR] Requested " + std::to_string(request_size) + " bytes, but will be allocated " + std::to_string(sizeof(void *)) + " bytes for further stable operation of the allocator.");

        request_size = sizeof(void*);
    }

    void *previous_block = nullptr;
    void *target_block = nullptr;
    void *previous_to_target_block = nullptr;
    void *next_to_target_block = nullptr;
    auto current_block = get_first_available_block();
    auto available_block_service_block_size = get_available_block_service_block_size();
    auto occupied_block_service_block_size = get_occupied_block_service_block_size();
    auto allocation_mode = get_allocation_mode();

    while (current_block != nullptr)
    {
        auto current_block_size = get_available_block_size(current_block);
        auto next_block = get_next_available_block(current_block);

        if (current_block_size >= request_size + occupied_block_service_block_size)
        {
            if (
                    allocation_mode == memory::allocation_mode::first_match ||
                    allocation_mode == memory::allocation_mode::the_best_match && (target_block == nullptr || current_block_size < get_available_block_size(target_block)) ||
                    allocation_mode == memory::allocation_mode::the_worst_match && (target_block == nullptr || current_block_size > get_available_block_size(target_block))
                    )
            {
                previous_to_target_block = previous_block;
                target_block = current_block;
                next_to_target_block = next_block;
            }

            if (allocation_mode == memory::allocation_mode::first_match)
            {
                break;
            }
        }

        previous_block = current_block;
        current_block = next_block;
    }

    if (target_block == nullptr)
    {
        std::string message = "No available memory";
        this->warning_with_guard("[SORTED LIST ALLOCATOR] " + message + ".");

        throw memory::memory_exception(message);
    }

    auto target_block_size = get_available_block_size(target_block);

    size_t leftover_size = target_block_size - request_size - occupied_block_service_block_size;

    if (leftover_size <= available_block_service_block_size && leftover_size != 0)
    {
        auto new_request_size = target_block_size - occupied_block_service_block_size;

        this->trace_with_guard("[SORTED LIST ALLOCATOR] Requested " + std::to_string(request_size) + " bytes, but for correct operation " + std::to_string(new_request_size) + " will be allocated.");

        request_size = new_request_size;
    }

    void * next_available_block_for_previous_block_ptr;

    if (request_size == target_block_size - occupied_block_service_block_size)
    {
        next_available_block_for_previous_block_ptr = next_to_target_block;
    }
    else
    {
        next_available_block_for_previous_block_ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(target_block) + occupied_block_service_block_size + request_size);

        auto * const rest_part_of_block_size = reinterpret_cast<size_t*>(next_available_block_for_previous_block_ptr);
        *rest_part_of_block_size = target_block_size - request_size - occupied_block_service_block_size;

        auto * const next_block_to_rest_part_of_block = reinterpret_cast<void**>(rest_part_of_block_size + 1);
        *next_block_to_rest_part_of_block = next_to_target_block;
    }

    if (previous_to_target_block == nullptr)
    {
        auto * const first_available_block = get_first_available_block_ptr();
        *first_available_block = next_available_block_for_previous_block_ptr;
    }
    else
    {
        *reinterpret_cast<void**>(reinterpret_cast<size_t*>(previous_to_target_block) + 1) = next_available_block_for_previous_block_ptr;
    }

    auto *target_block_size_space = reinterpret_cast<size_t*>(target_block);
    *target_block_size_space = request_size + occupied_block_service_block_size;

    auto allocated_block = reinterpret_cast<void*>(target_block_size_space + 1);

    this->trace_with_guard("[SORTED LIST ALLOCATOR] Memory allocation at address: " + address_to_string(get_address_relative_to_allocator(allocated_block)) + " success.");

    return reinterpret_cast<void*>(allocated_block);
}

void sorted_list_alloc::deallocate(void * target_to_dealloc) const
{
    auto * target_block = reinterpret_cast<void*>(reinterpret_cast<size_t*>(target_to_dealloc) - 1);

    if (target_block < _allocated_memory || target_block > reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(_allocated_memory) + get_allocated_memory_size()))
    {
        std::string message = "Block with address: " + address_to_string(target_to_dealloc) + " does not belong to the allocator";
        this->warning_with_guard("[SORTED LIST ALLOCATOR] " + message + ".");

        throw memory::memory_exception(message);
    }

    memory_state_before_deallocation(target_to_dealloc, get_logger());

    void * previous_to_target_block = nullptr;
    auto next_to_target_block = get_first_available_block();

    while (next_to_target_block != nullptr && next_to_target_block < target_block)
    {
        previous_to_target_block = next_to_target_block;
        next_to_target_block = get_next_available_block(next_to_target_block);
    }

    auto target_block_size = get_occupied_block_size(target_to_dealloc);
    auto * const next_available_block_to_target_block = reinterpret_cast<void**>(reinterpret_cast<size_t*>(target_block) + 1);

    if (next_to_target_block != nullptr &&
    reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(target_block) + target_block_size) == next_to_target_block)
    {
        target_block_size = target_block_size + get_available_block_size(next_to_target_block);
        *next_available_block_to_target_block = get_next_available_block(next_to_target_block);
    }
    else
    {
        *next_available_block_to_target_block = next_to_target_block;
    }

    if (previous_to_target_block != nullptr) {

        auto * const next_available_block_for_previous_block = reinterpret_cast<void**>(reinterpret_cast<size_t*>(previous_to_target_block) + 1);

        if (reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(previous_to_target_block) + get_available_block_size(previous_to_target_block)) == target_block)
        {
            auto *const previous_to_target_block_size_space = reinterpret_cast<size_t *>(previous_to_target_block);
            *previous_to_target_block_size_space += target_block_size;

            *next_available_block_for_previous_block = *next_available_block_to_target_block;
        }
        else
        {
            auto * const target_block_size_space = reinterpret_cast<size_t *>(target_block);
            *target_block_size_space = target_block_size;

            *next_available_block_for_previous_block = target_block;
        }
    }
    else
    {
        auto * const target_block_size_space = reinterpret_cast<size_t *>(target_block);
        *target_block_size_space = target_block_size;

        auto * const first_available_block = get_first_available_block_ptr();
        *first_available_block = target_block;
    }

    this->trace_with_guard("[SORTED LIST ALLOCATOR] Memory at address: " + address_to_string(get_address_relative_to_allocator(target_to_dealloc)) + " was deallocated.");
}



sorted_list_alloc::~sorted_list_alloc()
{
    const auto * const outer_allocator = get_outer_allocator();

    this->trace_with_guard("[SORTED LIST ALLOCATOR] Allocator success deleted.");

    if (outer_allocator == nullptr)
    {
        ::operator delete(_allocated_memory);
    }
    else
    {
        outer_allocator->deallocate(_allocated_memory);
    }
}