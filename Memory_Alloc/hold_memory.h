#ifndef MEMORY_HOLDER_H
#define MEMORY_HOLDER_H
#include "memory.h"

class hold_memory
{
public:

    void * const allocate_with_guard(size_t) const;

    void deallocate_with_guard(void *) const;

protected:

    virtual memory * get_outer_allocator() const = 0;

public:

    virtual ~hold_memory() = default;
};


#endif //MEMORY_HOLDER_H
