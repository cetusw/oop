#include "../PrimeNumbersGenerator.h"
#include "catch2/catch_all.hpp"

#include <iostream>

void PrimeNumbersGeneratorTest(
	const int testBound, const int expectedPrimesCount, const std::string& description)
{
	SECTION(description)
	{
		REQUIRE(GeneratePrimeNumbersSet(testBound).size() == expectedPrimesCount);
	}
}

TEST_CASE("PrimeNumbersGeneratorTest")
{
	PrimeNumbersGeneratorTest(0, 0, "Ноль");
	PrimeNumbersGeneratorTest(1, 0, "Один");
	PrimeNumbersGeneratorTest(2, 1, "Два");
	PrimeNumbersGeneratorTest(10, 4, "Какое-то рандомное число");
	PrimeNumbersGeneratorTest(100000000, 5761455, "Макс значение");
	PrimeNumbersGeneratorTest(-1, 0, "Отрицательное значение");

}