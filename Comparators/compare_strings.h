#ifndef STRING_COMPARER_H
#define STRING_COMPARER_H

#include "../Data_Types/data_type.h"

class compare_strings final
{

public:

    int operator()(std::string const & first, std::string const & second);
};


#endif //STRING_COMPARER_H
