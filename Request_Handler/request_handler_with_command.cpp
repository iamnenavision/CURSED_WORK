#include "request_handler_with_command.h"

request_handler_with_command::request_handler_with_command(command *target_action) : _target_action(target_action)
{

}

request_handler_with_command::~request_handler_with_command() noexcept
{
    delete _target_action;
}

bool request_handler_with_command::handle(const std::string &request) const noexcept
{
    if (!_target_action->can_execute(request))
    {
        if (handler::_next_handler == nullptr)
        {
            return false;
        }

        return handler::_next_handler->handle(request);
    }

    _target_action->execute(request);

    return true;
}