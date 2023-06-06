#include <iostream>
#include "Data_structures/database.h"
#include <fstream>

int main(int argc, char *argv[])
{

    database * db = new database();

    std::string command;

    std::ifstream file("../Test/test_data.txt");

    while (std::getline(file, command))
    {
        db->handle_request(command);
    }

    delete db;

    getchar();

    return 0;
}
