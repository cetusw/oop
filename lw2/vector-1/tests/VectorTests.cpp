#include <iostream>

#include "../Vector.h"
#include "../VectorUtils.h"
#include "catch2/catch_all.hpp"
#include <catch2/catch_approx.hpp>

struct TestData
{
    std::vector<std::vector<float> > testVectors = {
        {1.0},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {-1, -2, -3},
        {-1, -2, 10},
        {1.1, 1.1, 1.1},
        {-1.5, -2.4, -3.44, -4.44, -53.3, -6.4, -7.4, -8.4, -9.4, -10.4},
        {-1, 1, -1, 2},
        {0.0, -1.0, 3.5},
        {}
    };
    std::vector<std::string> testStrings = {
        "1.0 \n",
        "1 2 3 4 5 6 7 8 9 10 \n",
        "-1 -2 -3 \n",
        "-1 -2 10 \n",
        "1.1 1.1 1.1 \n",
        "-1.5 -2.4 -3.44 -4.44 -53.3 -6.4 -7.4 -8.4 -9.4 -10.4 \n",
        "-1 1 -1 2 \n",
        "0.0 -1.0 3.5 \n",
        ""
    };
    std::vector<std::string> testSortedStrings = {
        "1.000 \n",
        "1.000 2.000 3.000 4.000 5.000 6.000 7.000 8.000 9.000 10.000 \n",
        "-3.000 -2.000 -1.000 \n",
        "-2.000 -1.000 10.000 \n",
        "1.100 1.100 1.100 \n",
        "-53.300 -10.400 -9.400 -8.400 -7.400 -6.400 -4.440 -3.440 -2.400 -1.500 \n",
        "-1.000 -1.000 1.000 2.000 \n",
        "-1.000 0.000 3.500 \n",
        "\n"
    };
    std::vector<float> GetSumOfPositivesTestExpectedValues = {
        1.0f,
        55.0f,
        0.0f,
        10.0f,
        3.3f,
        0.0f,
        3.0f,
        3.5f,
        0.0f,
    };
    std::vector<float> GetPositivesNumbersCountTestExpectedValues = {
        1,
        10,
        0,
        1,
        3,
        0,
        2,
        1,
        0,
    };

    std::vector<std::vector<float> > processNumbersTestExpectedValues = {
        {2.0},
        {6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5},
        {-1, -2, -3},
        {9.0, 8.0, 20.0},
        {2.2, 2.2, 2.2},
        {-1.5, -2.4, -3.44, -4.44, -53.3, -6.4, -7.4, -8.4, -9.4, -10.4},
        {0.5, 2.5, 0.5, 3.5},
        {3.5, 2.5, 7.0},
        {}
    };
};

void RunProcessNumbersTests(const std::vector<std::vector<float> > &vector,
                            std::vector<std::vector<float> > expectedValue)
{
    for (int i = 0; i < vector.size(); i++)
    {
        SECTION("Тест #" + std::to_string(i))
        {
            std::vector<float> numbers = vector[i];
            ProcessNumbers(numbers);
            REQUIRE(numbers == expectedValue[i]);
        }
    }
}

void RunGetSumOfPositivesTests(std::vector<std::vector<float> > vector, const std::vector<float> &expectedValue)
{
    for (int i = 0; i < vector.size(); i++)
    {
        SECTION("Тест #" + std::to_string(i))
        {
            REQUIRE(GetSumOfPositives(vector[i]) == Catch::Approx(expectedValue[i]));
        }
    }
}

void RunGetPositivesNumbersCountTests(const std::vector<std::vector<float> > &vector, const std::vector<float> &expectedValue)
{
    for (int i = 0; i < vector.size(); i++)
    {
        SECTION("Тест #" + std::to_string(i))
        {
            REQUIRE(GetPositivesNumbersCount(vector[i]) == expectedValue[i]);
        }
    }
}

void RunReadNumbersTests(const std::vector<std::string> &inputString,
                         const std::vector<std::vector<float> > &expectedValue)
{
    for (int i = 0; i < inputString.size(); i++)
    {
        SECTION("Тест #" + std::to_string(i))
        {
            std::vector<float> numbers;

            const std::istringstream input(inputString[i]);
            const auto oldCinBuf = std::cin.rdbuf(input.rdbuf());

            ReadNumbers(numbers);
            std::cin.rdbuf(oldCinBuf);

            REQUIRE(numbers == expectedValue[i]);
        }
    }
}

void RunPrintSortedNumbersTests(const std::vector<std::vector<float> > &inputVector,
                                const std::vector<std::string> &expectedValue)
{
    for (int i = 0; i < inputVector.size(); i++)
    {
        SECTION("Тест #" + std::to_string(i))
        {
            std::vector numbers = inputVector[i];

            const std::stringstream buffer;
            const auto oldCinBuf = std::cout.rdbuf(buffer.rdbuf());

            PrintSortedNumbers(numbers);

            std::cout.rdbuf(oldCinBuf);

            REQUIRE(buffer.str() == expectedValue[i]);
        }
    }
}

TEST_CASE("GetSumOfPositives TEST")
{
    const TestData data;
    RunGetSumOfPositivesTests(data.testVectors, data.GetSumOfPositivesTestExpectedValues);
}

TEST_CASE("GetPositivesNumbersCount TEST")
{
    const TestData data;
    RunGetPositivesNumbersCountTests(data.testVectors, data.GetPositivesNumbersCountTestExpectedValues);
}

TEST_CASE("ProcessNumbers TEST")
{
    const TestData data;
    RunProcessNumbersTests(data.testVectors, data.processNumbersTestExpectedValues);
}

TEST_CASE("ReadNumbers TEST")
{
    const TestData data;
    RunReadNumbersTests(data.testStrings, data.testVectors);

    SECTION("Тест #" + std::to_string(data.testStrings.size()))
    {
        std::vector<float> numbers;

        const std::istringstream input("1.5 2.3 a\n");
        const auto oldCinBuf = std::cin.rdbuf(input.rdbuf());

        REQUIRE_THROWS_AS(ReadNumbers(numbers), std::invalid_argument);
        REQUIRE_THROWS_WITH(ReadNumbers(numbers), "ERROR");

        std::cin.rdbuf(oldCinBuf);
    }
}


TEST_CASE("PrintSortedNumbers TEST")
{
    const TestData data;
    RunPrintSortedNumbersTests(data.testVectors, data.testSortedStrings);
}

// написать функцию, которая принимает вектор и ожидаемое значение
