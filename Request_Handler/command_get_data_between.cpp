#include "command_get_data_between.h"
#include "../Data_structures/database.h"

bool command_get_data_between::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("GET_RANGE"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 8)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];


            std::stringstream build_id(argc[4]);
            build_id >> _build_id_for_first_key;

            std::stringstream build_version(argc[5]);
            build_version >> _build_version_for_first_key;

            std::stringstream build_id2(argc[6]);
            build_id2 >> _build_id_for_second_key;

            std::stringstream build_version2(argc[7]);
            build_version2 >> _build_version_for_second_key;


            return true;
        }
        else
        {
            std::cout<<"GET_RANGE ERROR: Wrong number of arguments!"<<std::endl;
        }
    }

    return false;
}

void command_get_data_between::execute(const std::string &request) const noexcept
{
    key * first_key = new key();

    first_key->_build_id = _build_id_for_first_key;
    first_key->_build_version = _build_version_for_first_key;
    key * second_key = new key();

    second_key->_build_id = _build_id_for_second_key;
    second_key->_build_version = _build_version_for_second_key;

    database::get_instance()->get_data_between_keys(
            _pool_name,
            _scheme_name,
            _collection_name,
            first_key,
            second_key);

    delete first_key;
    delete second_key;
}