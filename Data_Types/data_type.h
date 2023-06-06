#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <iostream>


struct key
{
    unsigned int _build_id;
    unsigned int _build_version;
};

struct value
{
    std::string _hash;
    std::string _login;
    std::string _build_name;
    std::string _build_errors;
    std::string _autotest_and_stat_analysis_errors;
    std::string _email_contact;
    std::string _build_path;
    std::string _build_artifacts;
};


#endif //DATA_TYPE_H
