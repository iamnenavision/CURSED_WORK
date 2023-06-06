#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

#include "../Data_Types/data_type.h"
#include "../Comparators/compare_strings.h"
#include "../Comparators/compare_keys.h"
#include "../Memory_Alloc/memory.h"
#include "../Memory_Alloc/global_heap_alloc.h"
#include "../Memory_Alloc/sorted_list_alloc.h"
#include "../Memory_Alloc/border_descriptors_alloc.h"
#include "../Memory_Alloc/buddy_alloc.h"
#include "../Trees/binary_search_tree.h"
#include "../Trees/splay_tree.h"

class data_collection final : protected hold_memory
{

private:

    memory * _allocator;

    associative_container<key*, value*> * _data;

public:

    data_collection(memory * allocator = nullptr);

    ~data_collection();

public:

    void add(
            unsigned int build_id,
            unsigned int build_version,
            const std::string &hash,
            const std::string &login,
            const std::string &build_name,
            const std::string &build_errors,
            const std::string &autotest_and_stat_analysis_errors,
            const std::string &email_contact,
            const std::string &build_path,
            const std::string &build_artifacts);

    value remove(key * data_key);

    value * get(key * const & data_key);

    std::vector<value *> get_between_keys(key * const & min_key, key * const & max_key);

    void update(
            unsigned int build_id,
            unsigned int build_version,
            const std::string & hash,
            const std::string & login,
            const std::string & build_name,
            const std::string & build_errors,
            const std::string & autotest_and_stat_analysis_errors,
            const std::string & email_contact,
            const std::string & build_path,
            const std::string & build_artifacts);

public:

    data_collection(data_collection const & other);

    data_collection & operator=(data_collection const & other);

    data_collection(data_collection && other) noexcept;

    data_collection & operator=(data_collection && other) noexcept;

private:

    memory * get_outer_allocator() const override;

};


#endif //DATA_COLLECTION_H
