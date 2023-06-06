#include "data_collection.h"

data_collection::data_collection(memory * allocator): _data(new splay_tree<key*, value*, key_comparer>(allocator, nullptr)), _allocator(allocator)
{

}

void data_collection::add(
        unsigned int build_id,
        unsigned int build_version,
        const std::string &hash,
        const std::string &login,
        const std::string &build_name,
        const std::string &build_errors,
        const std::string &autotest_and_stat_analysis_errors,
        const std::string &email_contact,
        const std::string &build_path,
        const std::string &build_artifacts)
{
    key * data_key = reinterpret_cast<key*>(allocate_with_guard(sizeof(key)));
    new (data_key) key;

    data_key->_build_id = build_id;
    data_key->_build_version = build_version;

    value * data_value = reinterpret_cast<value*>(allocate_with_guard(sizeof(value)));
    new (data_value) value;

    data_value->_hash = hash;
    data_value->_login = login;
    data_value->_build_name = build_name;
    data_value->_build_errors = build_errors;
    data_value->_autotest_and_stat_analysis_errors = autotest_and_stat_analysis_errors;
    data_value->_email_contact = email_contact;
    data_value->_build_path = build_path;
    data_value->_build_artifacts = build_artifacts;

    _data->insert(data_key, std::move(data_value));
}

value data_collection::remove(key * data_key)
{
    auto returned_node = _data->remove_node(data_key);

    value result = *(std::get<1>(returned_node));

    std::get<0>(returned_node)->~key();
    deallocate_with_guard(std::get<0>(returned_node));

    std::get<1>(returned_node)->~value();
    deallocate_with_guard(std::get<1>(returned_node));

    return result;
}

value * data_collection::get(key * const & data_key)
{
    return _data->get_value(data_key);
}

std::vector<value *> data_collection::get_between_keys(key *const &min_key, key *const &max_key)
{
    return _data->find_in_range(min_key, max_key);
}

void data_collection::update(
        unsigned int build_id,
        unsigned int build_version,
        const std::string & hash,
        const std::string & login,
        const std::string & build_name,
        const std::string & build_errors,
        const std::string & autotest_and_stat_analysis_errors,
        const std::string & email_contact,
        const std::string & build_path,
        const std::string & build_artifacts)
{
    key * data_key = reinterpret_cast<key*>(allocate_with_guard(sizeof(key)));
    new (data_key) key;

    data_key->_build_id = build_id;
    data_key->_build_version = build_version;

    value * data_value = reinterpret_cast<value*>(allocate_with_guard(sizeof(value)));
    new (data_value) value;

    data_value->_hash = hash;
    data_value->_build_name = build_name;
    data_value->_build_errors = build_errors;
    data_value->_autotest_and_stat_analysis_errors = autotest_and_stat_analysis_errors;
    data_value->_email_contact = email_contact;
    data_value->_build_path = build_path;
    data_value->_build_artifacts = build_artifacts;

    _data->update(data_key, std::move(data_value));

    data_key->~key();
    deallocate_with_guard(data_key);
}

memory * data_collection::get_outer_allocator() const
{
    return _allocator;
}

data_collection::data_collection(const data_collection &other)
    : _data(new splay_tree<key*, value*, key_comparer>(*reinterpret_cast<splay_tree<key*, value*, key_comparer>*>(other._data))), _allocator(other._allocator)
{

}

data_collection::data_collection(data_collection &&other) noexcept
{
    this->_data = other._data;
    this->_allocator = other._allocator;

    other._data = nullptr;
    other._allocator = nullptr;
}

data_collection &data_collection::operator=(const data_collection &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_data;

    if (this->_allocator != other._allocator)
    {
        delete this->_allocator;
        this->_allocator = other._allocator;
    }

    this->_data = new splay_tree<key*, value*, key_comparer>(*reinterpret_cast<splay_tree<key*, value*, key_comparer>*>(other._data));

    return *this;
}

data_collection &data_collection::operator=(data_collection &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_data;
    delete this->_allocator;

    this->_data = other._data;
    this->_allocator = other._allocator;

    other._data = nullptr;
    other._allocator = nullptr;

    return *this;
}

data_collection::~data_collection()
{
    delete _data;
}