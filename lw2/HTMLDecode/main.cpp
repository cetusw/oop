#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include "HTMLDecoder.h"

int main(const int argc, char *argv[])
{
    try
    {
        if (argc == 3)
        {
            HTMLDecode(argv[1], argv[2]);
        } else
        {
            throw std::invalid_argument("ERROR");
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}

// убрать классы +
// разнести логику GetHTMLEntity + использовать map ++
// переписать тесты +

