#include "command.h"

std::vector<std::string> command::split(const std::string &text, char delim) const
{
    std::vector<std::string> result;
    std::string token;
    std::istringstream tokenStream(text);
    while (std::getline(tokenStream, token, delim))
    {
        result.push_back(token);
    }
    return result;
}
