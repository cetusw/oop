#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>

#include "Vector.h"
#include "VectorUtils.h"

void ReadNumbers(std::vector<float> &numbers)
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

void ProcessNumbers(std::vector<float> &numbers)
{
    const long numberOfPositive = GetPositivesNumbersCount(numbers);
    if (numberOfPositive <= 0)
    {
        return;
    }
    const float sumOfPositive = GetSumOfPositives(numbers);
    const float arithmeticMean = sumOfPositive / static_cast<float>(numberOfPositive);
    std::ranges::transform(numbers, numbers.begin(),
                           [arithmeticMean](const float number)
                           {
                               return number + arithmeticMean;
                           });
    // std::transform
}

void PrintSortedNumbers(std::vector<float> &numbers)
{
    std::ranges::sort(numbers);
    for (const float number: numbers)
    {
        std::cout << std::fixed << std::setprecision(3) << number << " ";
    }
    std::cout << std::endl;
}

float GetSumOfPositives(std::vector<float> &numbers)
{
    return std::accumulate(numbers.begin(), numbers.end(), 0.0f,
                           [](const float accumulator, const float currentValue)
                           {
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

long GetPositivesNumbersCount(const std::vector<float> &numbers)
{
    return std::ranges::count_if(numbers, [](const float number) { return number > 0; });
}
