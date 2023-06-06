#ifndef POOL_H
#define POOL_H

#include "scheme.h"

class pool final
{

private:

    memory * _allocator;

    associative_container<std::string, scheme> * _pool;

public:

    pool(memory * allocator = nullptr);

    ~pool();

public:

    void add(std::string const & key, scheme && target);

    void remove(std::string const & key);

    scheme const & find(std::string const & scheme_name) const;

    memory * get_allocator() const;

public:

    pool(pool const & other);

    pool & operator=(pool const & other);

    pool(pool && other) noexcept;

    pool & operator=(pool && other) noexcept;

};


#endif //POOL_H
