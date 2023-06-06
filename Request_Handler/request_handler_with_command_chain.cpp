#include "request_handler_with_command_chain.h"

request_handler_with_command_chain::request_handler_with_command_chain() : _first_handler(nullptr), _last_handler(nullptr)
{

}

request_handler_with_command_chain::~request_handler_with_command_chain()
{
    while (_first_handler != nullptr)
    {
        _last_handler = _first_handler;
        _first_handler = _first_handler->_next_handler;
        delete _last_handler;
    }
}

bool request_handler_with_command_chain::handle(const std::string &request) const noexcept
{
    if (_first_handler == nullptr)
    {
        return false;
    }

    return _first_handler->handle(request);
}

request_handler_with_command_chain &request_handler_with_command_chain::add_handler(command *cmd)
{
    _last_handler = _first_handler == nullptr ?
            _first_handler = new request_handler_with_command(cmd) :
            _last_handler->_next_handler = new request_handler_with_command(cmd);

    return *this;
}
