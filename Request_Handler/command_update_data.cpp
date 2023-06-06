#include "command_update_data.h"
#include "../Data_structures/database.h"

bool command_update_data::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("UPDATE_DATA"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 14)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];


            std::stringstream build_id(argc[4]);
            build_id >> _build_id;


            std::stringstream build_version(argc[5]);
            build_version >> _build_version;

            _hash = argc[6];
            _login = argc[7];
            _build_name = argc[8];
            _build_errors = argc[9];
            _autotest_and_stat_analysis_errors = argc[10];

            _email_contact = argc[11];

            _build_path = argc[12];

            std::stringstream build_artifacts(argc[13]);
            build_artifacts >> _build_artifacts;

            return true;
        }
        else {
            std::cout<<"UPDATE_DATA ERROR: Wrong number of arguments!"<<std::endl;
        }
    }

    return false;
}

void command_update_data::execute(const std::string &request) const noexcept
{
    database::get_instance()->update_data(
            _pool_name,
            _scheme_name,
            _collection_name,
            _build_id,
            _build_version,
            _hash,
            _login,
            _build_name,
            _build_errors,
            _autotest_and_stat_analysis_errors,
            _email_contact,
            _build_path,
            _build_artifacts);
}