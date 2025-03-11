#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

class Vector {
public:
	static void ReadNumbers(std::vector<float>& numbers);
	static void ProcessNumbers(std::vector<float>& numbers);
	static void PrintSortedNumbers(std::vector<float>& numbers);
private:
};



#endif //VECTOR_H
