#include "command_get_data.h"
#include "../Data_structures/database.h"

bool command_get_data::can_execute(const std::string &request)noexcept
{
    if (request.starts_with("GET_DATA"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 6)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];


            std::stringstream build_id(argc[4]);
            build_id >> _build_id;



            std::stringstream build_version(argc[5]);
            build_version >> _build_version;

            return true;
        }
        else
        {
            std::cout<<"GET_DATA ERROR: Wrong Number of arguments"<<std::endl;
        }
    }

    return false;
}

void command_get_data::execute(const std::string &request) const noexcept
{
    key * data_key = new key();

    data_key->_build_id = _build_id;
    data_key->_build_version = _build_version;

    database::get_instance()->get_data(_pool_name, _scheme_name, _collection_name, data_key);

    delete data_key;
}