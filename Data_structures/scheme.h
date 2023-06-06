#ifndef SCHEME_H
#define SCHEME_H

#include "data_collection.h"

class scheme final
{
    friend class database;

private:

    associative_container<std::string, data_collection> * _scheme;

public:

    scheme();

    ~scheme();

public:

    void add(std::string const &key, data_collection && target);

    void remove(std::string const & key);

    data_collection const & find(std::string const & collection_name) const;

public:

    scheme(scheme const & other);

    scheme & operator=(scheme const & other);

    scheme(scheme && other) noexcept;

    scheme & operator=(scheme && other) noexcept;

};


#endif //SCHEME_H
