#ifndef ASSOCIATIVE_CONTAINER_H
#define ASSOCIATIVE_CONTAINER_H
#include <iostream>
#include <vector>

template<typename tkey, typename tvalue>
class associative_container
{

public:

    enum class mode
    {
        INSERT,
        UPDATE
    };

public:

    struct key_value_pair final
    {
        tkey _key;
        tvalue _value;
    };

public:

    virtual void insert(tkey const &key, tvalue &&value) = 0;

    virtual void update(tkey const &key, tvalue &&value) = 0;

    virtual bool find(key_value_pair * target_key_and_result_value) = 0;

    virtual tvalue const &find(tkey const &key) = 0;

    tvalue get_value(tkey const & key);

    virtual std::vector<tvalue> find_in_range(tkey const & min_bound, tkey const & max_bound) = 0;

    virtual std::tuple<tkey, tvalue> remove_node(tkey const &key) = 0;

    virtual tvalue remove(tkey const &key) = 0;

public:

    void operator+=(key_value_pair pair);

    bool operator[](key_value_pair * target_key_and_result_value);

    tvalue && operator-=(tkey const &key);

public:

    virtual ~associative_container() = default;

};

template<
    typename tkey,
    typename tvalue>
tvalue associative_container<tkey, tvalue>::get_value(tkey const & key)
{
    return find(key);
//    key_value_pair key_and_value {std::move(key)};
//
//    if ((*this).find(&key_and_value))
//    {
//        return key_and_value._value;
//    }
//    return key_and_value._value;
}

template<
    typename tkey,
    typename tvalue>
void associative_container<tkey, tvalue>::operator+=(key_value_pair pair)
{
    insert(pair._key, std::move(pair._value));
}

template<
    typename tkey,
    typename tvalue>
bool associative_container<tkey, tvalue>::operator[](key_value_pair *target_key_and_result_value)
{
    return find(target_key_and_result_value);
}

template<
    typename tkey,
    typename tvalue>
tvalue && associative_container<tkey,tvalue>::operator-=(const tkey &key)
{
    return std::move(remove(key));
}

#endif //ASSOCIATIVE_CONTAINER_H
