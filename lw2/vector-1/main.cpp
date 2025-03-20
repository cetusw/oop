#include <iostream>
#include "Vector.h"

int main()
{
	try
	{
		std::vector<float> numbers;
		ReadNumbers(numbers);
		ProcessNumbers(numbers);
		PrintSortedNumbers(numbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

// написать тесты +

// убрать инклуды из хедеров +
// убрать классы +
