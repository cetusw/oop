#include "../Vector.h"
#include "../VectorUtils.h"
#include "catch2/catch_all.hpp"

const char* programName = "./vector";
TEST_CASE("Test vector process") {

    std::vector<float> vectorOfIntPositives = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::vector<float> vectorOfIntNegatives = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
    const std::vector<float> vectorOfIntMixed = {-1, -2, -3, 4, -5, 6, -7, 8, -9, 10};
    const std::vector<float> vectorOfFloatPositives = {1.11, 2.12, 3.33, 4.44, 5.44, 6.55, 76.6, 4.4, 9.4, 10.4};
    const std::vector<float> vectorOfFloatNegatives = {-1.5, -2.4, -3.44, -4.44, -53.3, -6.4, -7.4, -8.4, -9.4, -10.4};
    const std::vector<float> vectorOfFloatMixed = {-1.5, -2.55, -3.55, 4, -5.55, 6.55, -7.55, 8, -9.55, 10.5};
    const std::vector<float> emptyVector;

    SECTION("Vector of positive integers") {
        REQUIRE(VectorUtils::GetSumOfPositives(vectorOfIntPositives) == 55);
    }
}