#ifndef REQUEST_HANDLER_WITH_COMMAND_CHAIN_H
#define REQUEST_HANDLER_WITH_COMMAND_CHAIN_H

#include "request_handler_with_command.h"

class request_handler_with_command_chain final
{

private:

    handler * _first_handler;
    handler * _last_handler;

public:

    request_handler_with_command_chain();
    ~request_handler_with_command_chain();

    request_handler_with_command_chain(request_handler_with_command_chain const &) = delete;
    request_handler_with_command_chain(request_handler_with_command_chain &&) = delete;
    request_handler_with_command_chain &operator=(request_handler_with_command_chain const &) = delete;
    request_handler_with_command_chain &operator=(request_handler_with_command_chain &&) = delete;

public:

    bool handle(std::string const & request) const noexcept;

public:

    request_handler_with_command_chain & add_handler(command * cmd);

};
#endif //REQUEST_HANDLER_WITH_COMMAND_CHAIN_H
