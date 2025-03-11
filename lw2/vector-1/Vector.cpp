#include "Vector.h"
#include "VectorUtils.h"

void Vector::ReadNumbers(std::vector<float>& numbers)
{
	float number;
	while (std::cin >> number)
	{
		numbers.push_back(number);
	}
	if (std::cin.fail() && !std::cin.eof())
	{
		throw std::invalid_argument("ERROR");
	}
}

float VectorUtils::GetSumOfPositives(std::vector<float>& numbers)
{
	return std::accumulate(numbers.begin(), numbers.end(), 0.0f,
		[](const float accumulator, const float currentValue) {
			if (currentValue > 0)
			{
				if (accumulator > std::numeric_limits<float>::max() - currentValue)
				{
					throw std::overflow_error("ERROR");
				}
				return accumulator + currentValue;
			}
			return accumulator;
		});
}

long VectorUtils::GetPositivesNumbersCount(const std::vector<float>& numbers)
{
	return std::ranges::count_if(numbers, [](const float number) { return number > 0; });
}

void Vector::ProcessNumbers(std::vector<float>& numbers)
{
	const long numberOfPositive = VectorUtils::GetPositivesNumbersCount(numbers);
	if (numberOfPositive <= 0)
	{
		return;
	}
	const float sumOfPositive = VectorUtils::GetSumOfPositives(numbers);
	const float arithmeticMean = sumOfPositive / static_cast<float>(numberOfPositive);
	for (float& number : numbers)
	{
		number += arithmeticMean;
	}
}

void Vector::PrintSortedNumbers(std::vector<float>& numbers)
{
	std::ranges::sort(numbers);
	for (const float number : numbers)
	{
		std::cout << std::fixed << std::setprecision(3) << number << " ";
	}
	std::cout << std::endl;
}