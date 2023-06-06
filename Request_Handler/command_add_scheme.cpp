#include "command_add_scheme.h"
#include "../Data_structures/database.h"

bool command_add_scheme::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("ADD_SCHEME"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 3)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];

            return true;
        }
        else {
            std::cout<<"ADD_SCHEME ERROR: Wrong number of arguments!"<<std::endl;
        }
    }

    return false;
}

void command_add_scheme::execute(const std::string &request) const noexcept
{
    database::get_instance()->add_scheme(_pool_name, _scheme_name);
}