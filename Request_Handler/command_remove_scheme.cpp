#include "command_remove_scheme.h"
#include "../Data_structures/database.h"

bool command_remove_scheme::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("REMOVE SCHEME"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 3)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];

            return true;
        }
        else {
            std::cout<<"REMOVE SCHEME ERROR: Wrong number of arguments!"<<std::endl;
        }
    }
    return false;
}

void command_remove_scheme::execute(const std::string &request) const noexcept
{
    database::get_instance()->remove_scheme(_pool_name, _scheme_name);
}