#include "compare_keys.h"

int key_comparer::operator()(key * first, key * second)
{
    int differences_count = first->_build_id - second->_build_id;
    if (differences_count != 0)
    {
        return differences_count;
    }

    differences_count = first->_build_version - second->_build_version;
        return differences_count;
}