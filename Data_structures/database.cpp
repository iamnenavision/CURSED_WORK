#include <cmath>
#include <iostream>

#include "database.h"
#include "../Request_Handler/command_add_pool.h"
#include "../Request_Handler/command_remove_pool.h"
#include "../Request_Handler/command_add_scheme.h"
#include "../Request_Handler/command_remove_scheme.h"
#include "../Request_Handler/command_add_collection.h"
#include "../Request_Handler/command_remove_collection.h"
#include "../Request_Handler/command_add_data.h"
#include "../Request_Handler/command_get_data.h"
#include "../Request_Handler/command_get_data_between.h"
#include "../Request_Handler/command_update_data.h"
#include "../Request_Handler/command_remove_data.h"

database *database::_instance = nullptr;

database::database()
{
    _database = new splay_tree<std::string, pool, compare_strings>();

    _chain
        .add_handler(new command_add_pool())
        .add_handler(new command_remove_pool())
        .add_handler(new command_add_scheme())
        .add_handler(new command_remove_scheme())
        .add_handler(new command_add_collection())
        .add_handler(new command_remove_collection())
        .add_handler(new command_add_data())
        .add_handler(new command_remove_data())
        .add_handler(new command_get_data())
        .add_handler(new command_get_data_between())
        .add_handler(new command_update_data());

    _instance = this;
}

database::~database()
{
    delete _database;
}

void database::add_pool(std::string const & pool_name, allocator_types allocator_name, size_t request_size, memory::allocation_mode mode)
{
    try
    {
        memory *allocator = nullptr;

        switch (allocator_name) {
            case allocator_types::GLOBAL_HEAP:
                allocator = new global_heap_alloc();
                break;

            case allocator_types::SORTED_LIST:
                allocator = new sorted_list_alloc(request_size, mode);
                break;

            case allocator_types::BORDER_DESCRIPTORS:
                allocator = new border_descriptors_allocator(request_size, mode);
                break;

            case allocator_types::BUDDIES_SYSTEM:
                request_size = static_cast<size_t>(log2(request_size)) + 1;
                allocator = new buddy_system_allocator(request_size, mode);
                break;
        }

        _database->insert(pool_name, std::move(pool(allocator)));

        std::cout << "DB Action: pool added to db" << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void database::add_scheme(std::string const & pool_name, std::string const & scheme_name)
{
    try
    {
        const_cast<pool &>(_database->find(pool_name)).add(scheme_name, std::move(scheme()));

        std::cout << "DB Action: scheme added to " << pool_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void database::add_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name)
{
    try
    {
        pool const &current_pool = _database->find(pool_name);

        memory *allocator = current_pool.get_allocator();

        scheme const &current_scheme = current_pool.find(scheme_name);

        const_cast<scheme &>(current_scheme).add(collection_name, std::move(data_collection(allocator)));

        std::cout << "DB Action: collection added to " << pool_name << " " << scheme_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void database::add_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        unsigned int build_id,
        unsigned int build_version,
        const std::string & hash,
        const std::string & login,
        const std::string & build_name,
        const std::string & name,
        const std::string & autotest_and_stat_analysis_errors,
        const std::string & email_contact,
        const std::string & build_path,
        const std::string & build_artifacts)
{
    try
    {
        const_cast<data_collection &>(
                _database
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).add(build_id, build_version, hash, login, build_name, name, autotest_and_stat_analysis_errors, email_contact, build_path, build_artifacts);

        std::cout << "DB Action: data added to " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void database::remove_pool(const std::string & pool_name)
{
    try
    {
        _database->remove(pool_name);

        std::cout << "DB Action: pool removed from db" << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void database::remove_scheme(const std::string & pool_name, const std::string & scheme_name)
{
    try
    {
        const_cast<pool &>(_database->find(pool_name)).remove(scheme_name);

        std::cout << "DB Action: scheme removed from " << pool_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void database::remove_collection(const std::string & pool_name, const std::string & scheme_name, const std::string & collection_name)
{
    try
    {
        const_cast<scheme &>(_database->find(pool_name).find(scheme_name)).remove(collection_name);

        std::cout << "DB Action: collection removed from " << pool_name << " " << scheme_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

value database::remove_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * data_key)
{
    value data;
    try
    {
        data = const_cast<data_collection &>(
                _database
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).remove(data_key);

        std::cout << "DB Action: data removed from " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;

        return data;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return data;
}

value * database::get_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * const & data_key)
{
    value * data;
    try
    {
        data = const_cast<data_collection &>(
                _database
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).get(data_key);

        std::cout << "DB Action: received value from " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;

        std::cout << "======Data======" << std::endl;
        std::cout << "Hash:" << data->_hash << std::endl;
        std::cout << "Login:" << data->_login << std::endl;
        std::cout << "Build name: " << data->_build_name << std::endl;
        std::cout << "Build errors: " << data->_build_errors << std::endl;
        std::cout << "Autotest and stat analysis errors: " << data->_autotest_and_stat_analysis_errors << std::endl;
        std::cout << "Email: " << data->_email_contact << std::endl;
        std::cout << "Build Path (Scenario): " << data->_build_path << std::endl;
        std::cout << "Build Artifacts Path: " << data->_build_artifacts << std::endl;
        std::cout << "=================="<<std::endl<<std::endl;
        return data;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return data;
}

std::vector<value *>database::get_data_between_keys(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key *const & min_key,
        key *const & max_key)
{
    std::vector<value *> data;
    try
    {
        data = const_cast<data_collection &>(
                _database
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).get_between_keys(min_key, max_key);

        std::cout << "DB Action: received values from " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;

        int index = 1;

        for (auto const & data_value : data)
        {
            std::cout << "======Data " << index << "======" << std::endl;
            std::cout << "Hash: " << data_value->_hash << std::endl;
            std::cout << "Login: " << data_value->_login << std::endl;
            std::cout << "Build_name: " << data_value->_build_name << std::endl;
            std::cout << "Build_errors: " << data_value->_build_errors << std::endl;
            std::cout << "Autotest and stat analysis errors: " << data_value->_autotest_and_stat_analysis_errors << std::endl;
            std::cout << "Email: " << data_value->_email_contact << std::endl;
            std::cout << "Build Path (Scenario): " << data_value->_build_path << std::endl;
            std::cout << "Build Artifacts Path: " << data_value->_build_artifacts << std::endl;
            std::cout << "=================="<<std::endl<<std::endl;
            index++;
        }

        return data;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return data;
}

void database::update_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        unsigned int build_id,
        unsigned int build_version,
        const std::string & hash,
        const std::string & login,
        const std::string & build_name,
        const std::string & name,
        const std::string & autotest_and_stat_analysis_errors,
        const std::string & email_contact,
        const std::string & build_path,
        const std::string & build_artifacts)
{
    try
    {
        const_cast<data_collection &>(
                _database
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).update(build_id, build_version, hash, login, build_name, name, autotest_and_stat_analysis_errors, email_contact, build_path, build_artifacts);

        std::cout << "DB Action: " << "email_contact from " << pool_name << " " << scheme_name << " " << collection_name <<  " updated" << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

database *database::get_instance()
{
    if (_instance == nullptr)
    {
        _instance = new database();
    }

    return _instance;
}

void database::handle_request(
        std::string const &request)
{
    _chain.handle(request);
}