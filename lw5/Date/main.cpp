#include "Date.h"

#include <iostream>
int main()
{
	Date date;
	std::cout << date.GetDay() << std::endl;
	std::cout << static_cast<int>(date.GetMonth()) << std::endl;
	std::cout << date.GetYear() << std::endl;
	std::cout << static_cast<int>(date.GetWeekDay()) << std::endl;
}