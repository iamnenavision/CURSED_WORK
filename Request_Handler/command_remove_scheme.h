#ifndef COMMAND_REMOVE_SCHEME_H
#define COMMAND_REMOVE_SCHEME_H

#include "command.h"

class command_remove_scheme final : public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;

public:

    bool can_execute(std::string const &request) noexcept final;

    void execute(std::string const &request) const noexcept final;

};

#endif //COMMAND_REMOVE_SCHEME_H
