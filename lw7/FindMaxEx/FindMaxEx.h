#ifndef FINDMAXEX_H
#define FINDMAXEX_H
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];
	for (const auto& item : arr)
	{
		if (less(maxValue, item))
		{
			maxValue = item;
		}
	}

	return true;
};

#endif // FINDMAXEX_H
