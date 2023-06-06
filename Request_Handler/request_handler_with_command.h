#ifndef REQUEST_HANDLER_WITH_COMMAND_H
#define REQUEST_HANDLER_WITH_COMMAND_H

#include "handler.h"
#include "command.h"

class request_handler_with_command : public handler
{

private:

    command * _target_action;

public:

    request_handler_with_command(command * target_action);

    ~request_handler_with_command();

    request_handler_with_command(request_handler_with_command const &) = delete;
    request_handler_with_command(request_handler_with_command &&) = delete;
    request_handler_with_command &operator=(request_handler_with_command const &) = delete;
    request_handler_with_command &operator=(request_handler_with_command &&) = delete;

public:

    bool handle(std::string const & request) const noexcept;

};

#endif //REQUEST_HANDLER_WITH_COMMAND_H
