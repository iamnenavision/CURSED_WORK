#ifndef COMMAND_REMOVE_POOL_H
#define COMMAND_REMOVE_POOL_H

#include "command.h"

class command_remove_pool final : public command
{

private:

    std::string _pool_name;

public:

    bool can_execute(std::string const &request) noexcept final;

    void execute(std::string const &request) const noexcept final;

};
#endif //COMMAND_REMOVE_POOL_H
