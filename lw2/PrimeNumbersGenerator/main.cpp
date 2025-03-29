#include <iostream>
#include <string>

#include "PrimeNumbersGenerator.h"

int main(const int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "ERROR" << std::endl;
		return 1;
	}

	int upperBound;
	try
	{
		upperBound = std::stoi(argv[1]);
		std::cout << upperBound << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR" << std::endl;
		return 1;
	}

	if (upperBound < 0 || upperBound > 100000000)
	{
		std::cerr << "ERROR" << std::endl;
		return 1;
	}

	const auto primes = GeneratePrimeNumbersSet(upperBound);
	for (const int prime : primes)
	{
		std::cout << prime << " ";
	}
	std::cout << std::endl;

	return 0;
}