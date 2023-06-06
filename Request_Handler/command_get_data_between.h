#ifndef COMMAND_GET_DATA_BETWEEN_H
#define COMMAND_GET_DATA_BETWEEN_H

#include "command.h"

class command_get_data_between final : public command
{

private:


    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
    unsigned int _build_id_for_first_key;
    unsigned int _build_version_for_first_key;
    unsigned int _build_id_for_second_key;
    unsigned int _build_version_for_second_key;

public:

    bool can_execute(std::string const &request) noexcept final;

    void execute(std::string const &request) const noexcept final;

};
#endif //COMMAND_GET_DATA_BETWEEN_H
