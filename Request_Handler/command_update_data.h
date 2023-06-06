#ifndef COMMAND_UPDATE_DATA_H
#define COMMAND_UPDATE_DATA_H

#include <iostream>
#include "command.h"

class command_update_data final : public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
    unsigned int _build_id;
    unsigned int _build_version;
    std::string _hash;
    std::string _login;
    std::string _build_name;
    std::string _build_errors;
    std::string _autotest_and_stat_analysis_errors;
    std::string _email_contact;
    std::string _build_path;
    std::string _build_artifacts;

public:

    bool can_execute(std::string const &request) noexcept final;

    void execute(std::string const &request) const noexcept final;

};

#endif //COMMAND_UPDATE_DATA_H
