#include <iostream>
#include <string>

#include "Car.h"

int main()
{
    Car car;
    std::string command;
    while (std::cin >> command)
    {
        car.ProcessInput(command);
    }

}
