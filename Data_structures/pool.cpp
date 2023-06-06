#include "pool.h"

pool::pool(memory * allocator): _pool(new splay_tree<std::string, scheme, compare_strings>()), _allocator(allocator)
{

}

void pool::add(const std::string & key, scheme && target)
{
    _pool->insert(key, std::move(target));
}

void pool::remove(const std::string & key)
{
    _pool->remove(key);
}

scheme const & pool::find(std::string const & scheme_name) const
{
    return _pool->find(scheme_name);
}

memory * pool::get_allocator() const
{
    return _allocator;
}

pool::pool(const pool &other)
    : _pool(new splay_tree<std::string, scheme, compare_strings>(*reinterpret_cast<splay_tree<std::string, scheme, compare_strings>*>(other._pool))), _allocator(other._allocator)
{

}

pool::pool(pool && other) noexcept
{
    this->_pool = other._pool;
    this->_allocator = other._allocator;

    other._pool = nullptr;
    other._allocator = nullptr;
}

pool &pool::operator=(const pool & other)
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_pool;

    if (this->_allocator != other._allocator)
    {
        delete this->_allocator;
        this->_allocator = other._allocator;
    }

    this->_pool = new splay_tree<std::string, scheme, compare_strings>(*reinterpret_cast<splay_tree<std::string, scheme, compare_strings>*>(other._pool));

    return *this;
}

pool &pool::operator=(pool && other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_pool;
    delete this->_allocator;

    this->_pool = other._pool;
    this->_allocator = other._allocator;

    other._pool = nullptr;
    other._allocator = nullptr;

    return *this;
}

pool::~pool()
{
    delete _pool;
    //delete _allocator;
}
