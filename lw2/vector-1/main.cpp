#include "Vector.h"

int main()
{
	try
	{
		std::vector<float> numbers;
		Vector::ReadNumbers(numbers);
		Vector::ProcessNumbers(numbers);
		Vector::PrintSortedNumbers(numbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

// написать тесты
// переименовать на GetPositivesNumbersCount + константная ссылка
// возвращать сразу GetSumOfPositives
// возвращать сразу GetPositivesNumbersCount
