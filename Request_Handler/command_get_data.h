#ifndef COMMAND_GET_DATA_H
#define COMMAND_GET_DATA_H

#include "command.h"

class command_get_data final : public command
{

private:


    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
    unsigned int _build_id;
    unsigned int _build_version;

public:

    bool can_execute(std::string const &request) noexcept final;

    void execute(std::string const &request) const noexcept final;

};
#endif //COMMAND_GET_DATA_H
