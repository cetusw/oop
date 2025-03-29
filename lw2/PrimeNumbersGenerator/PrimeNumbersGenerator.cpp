#include "PrimeNumbersGenerator.h"

#include <set>
#include <vector>

std::vector<bool> Sieve(const int n)
{
	std::vector sieve(n + 1, true);
	sieve[0] = false;
	sieve[1] = false;

	for (long i = 3; i <= n; i += 2)
	{
		if (sieve[i])
		{
			for (long j = i * i; j <= n; j += 2 * i)
			{
				sieve[j] = false;
			}
		}
	}

	return sieve;
}

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	std::set<int> primes;
	if (upperBound < 2)
	{
		return primes;
	}

	std::vector<bool> sieve = Sieve(upperBound);

	primes.insert(2);
	for (int i = 3; i <= upperBound; i += 2)
	{
		if (sieve[i])
		{
			primes.insert(i);
		}
	}

	return primes;
}