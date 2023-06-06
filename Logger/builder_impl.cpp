#include "builder_impl.h"
#include "logger_impl.h"

builder* builder_impl::add_stream(std::string const &target, logger::severity level)
{
    if (target.empty())
    {
        throw std::invalid_argument("empty file path");
    }

    _settings[target] = level;
    return this;
}

std::shared_ptr<logger> builder_impl::build() const
{
    return std::make_shared<logger_impl>(_settings);
}