#include "../PrimeNumbersGenerator.h"
#include "catch2/catch_all.hpp"

#include <iostream>

void PrimeNumbersGeneratorCountTest(
	const int testBound, const int expectedPrimesCount, const std::string& description)
{
	SECTION(description)
	{
		REQUIRE(GeneratePrimeNumbersSet(testBound).size() == expectedPrimesCount);
	}
}

void PrimeNumbersGeneratorValueTest(
	const int testBound, const std::set<int>& expectedPrimes, const std::string& description)
{
	SECTION(description) { REQUIRE(GeneratePrimeNumbersSet(testBound) == expectedPrimes); }
}

TEST_CASE("Count")
{
	PrimeNumbersGeneratorCountTest(0, 0, "Ноль");
	PrimeNumbersGeneratorCountTest(1, 0, "Один");
	PrimeNumbersGeneratorCountTest(2, 1, "Два");
	PrimeNumbersGeneratorCountTest(10, 4, "Какое-то рандомное число");
	PrimeNumbersGeneratorCountTest(100000000, 5761455, "Макс значение"); // только release
	PrimeNumbersGeneratorCountTest(-1, 0, "Отрицательное значение");
}

TEST_CASE("Value")
{
	PrimeNumbersGeneratorValueTest(0, {}, "Ноль");
	PrimeNumbersGeneratorValueTest(1, {}, "Один");
	PrimeNumbersGeneratorValueTest(2, { 2 }, "Два");
	PrimeNumbersGeneratorValueTest(10, { 2, 3, 5, 7 }, "Какое-то рандомное число");
	PrimeNumbersGeneratorValueTest(-1, {}, "Отрицательное значение");
	PrimeNumbersGeneratorValueTest(100,
		{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
			89, 97 },
		"Большое число");
}