#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>

class handler
{

    friend class request_handler_with_command_chain;

protected:

    handler * _next_handler;

public:

    handler() : _next_handler(nullptr) {}

    virtual ~handler() = default;

public:

    virtual bool handle(std::string const & request) const noexcept = 0;
};


#endif //HANDLER_H
