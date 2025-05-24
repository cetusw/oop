#ifndef FINDMAXEX_H
#define FINDMAXEX_H
#include <iostream>

#include <ostream>
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	T tempMax = arr[0];
	try
	{
		for (const auto& item : arr)
		{
			if (less(tempMax, item))
			{
				tempMax = item;
			}
		}
		maxValue = tempMax;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

#endif // FINDMAXEX_H
