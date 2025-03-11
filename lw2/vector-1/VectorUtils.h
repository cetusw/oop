#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <iostream>
#include <vector>

class VectorUtils {
public:
    static float GetSumOfPositives(std::vector<float>& numbers);
    static long GetPositivesNumbersCount(const std::vector<float>& numbers);
};

#endif //VECTORUTILS_H
