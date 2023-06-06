#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "pool.h"
#include "../Data_Types/allocator_types.h"
#include "../Request_Handler/request_handler_with_command_chain.h"

class database
{

private:

    static database * _instance;

private:

    request_handler_with_command_chain _chain;

private:

    associative_container<std::string, pool>  * _database;

public:

    database();

    ~database();

public:

    static database *get_instance();

public:

    void add_pool(std::string const & name_pool, allocator_types allocator_name, size_t request_size, memory::allocation_mode mode);

    void add_scheme(std::string const & pool_name, std::string const & scheme_name);

    void add_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name);

    void add_data(std::string const & pool_name,
         std::string const & scheme_name,
         std::string const & collection_name,
         unsigned int build_id,
         unsigned int build_version,
         std::string const & hash,
         std::string const & login,
         std::string const & build_name,
         std::string const & name,
         std::string const & autotest_and_stat_analysis_errors,
         std::string const & email_contact,
         std::string const & build_path,
         const std::string & build_artifacts
         );

    void remove_pool(std::string const & name);

    void remove_scheme(std::string const & pool_name, std::string const & scheme_name);

    void remove_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name);

    value remove_data(
            std::string const & pool_name,
            std::string const & scheme_name,
            std::string const & collection_name,
            key * data_key);

    void update_data(
            std::string const & pool_name,
            std::string const & scheme_name,
            std::string const & collection_name,
            unsigned int build_id,
            unsigned int build_version,
            std::string const & hash,
            std::string const & login,
            std::string const & build_name,
            std::string const & name,
            std::string const & autotest_and_stat_analysis_errors,
            std::string const & email_contact,
            std::string const & build_path,
            const std::string & build_artifacts);

    value * get_data(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name, key * const & data_key);

    std::vector<value*> get_data_between_keys(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name, key * const & min_key, key * const & max_key);

public:

    void handle_request(
            std::string const &request);

public:

    database(database const & other) = delete;

    database & operator=(database const & other) = delete;

    database(database && other) = delete;

    database & operator=(database && other) = delete;

};

#endif //DATA_BASE_H
