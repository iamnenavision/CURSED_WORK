#include "command_remove_collection.h"
#include "../Data_structures/database.h"

bool command_remove_collection::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("REMOVE COLLECTION"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 4)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];

            return true;
        }
        else {
            std::cout<<"REMOVE COLLECTION ERROR: Wrong number of arguments!"<<std::endl;
        }
    }

    return false;
}

void command_remove_collection::execute(const std::string &request) const noexcept
{
    database::get_instance()->remove_collection(_pool_name, _scheme_name, _collection_name);
}