#ifndef KEY_COMPARER_H
#define KEY_COMPARER_H

#include "../Data_Types/data_type.h"
#include "compare_strings.h"

class key_comparer final
{

private:

    compare_strings _string_comparer;

public:

    int operator()(key * first, key * second);

};


#endif //KEY_COMPARER_H
