#include "compare_strings.h"

int compare_strings::operator()(std::string const & first, std::string const & second)
{
    if (first > second)
        return 1;
    else if (first < second)
        return -1;
    else
        return 0;
}
