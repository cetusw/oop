#include "PrimeNumbersGenerator.h"

#include <cmath>
#include <set>
#include <vector>

std::vector<bool> GetSieve(const int n)
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

std::set<int> FindBasePrimes(const int limit)
{
	if (limit < 2)
	{
		return {};
	}
	const int sieveLimit = static_cast<int>(std::sqrt(limit));

	std::vector sieve = GetSieve(sieveLimit);

	std::set<int> primes;
	primes.insert(2);
	for (int i = 3; i <= sieveLimit; i += 2)
	{
		if (sieve[i])
		{
			primes.insert(i);
		}
	}
	return primes;
}

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	std::set<int> primes;
	if (upperBound < 2)
	{
		return primes;
	}

	const auto& basePrimes = FindBasePrimes(upperBound);
	const int segmentSize = static_cast<int>(std::sqrt(upperBound));

	primes.insert(2);
	for (int low = 3; low <= upperBound; low += segmentSize)
	{
		const int high = std::min(low + segmentSize - 1, upperBound);

		std::vector segment(high - low + 1, true);

		for (const int p : basePrimes)
		{
			const int first = std::max(p * p, (low + p - 1) / p * p);
			if (first > high)
			{
				continue;
			}

			for (int j = first; j <= high; j += p)
			{
				segment[j - low] = false;
			}
		}

		for (int i = 0; i < segment.size(); ++i)
		{
			int num = low + i;
			if (num % 2 == 0)
			{
				continue;
			}
			if (segment[i] && num <= upperBound)
			{
				primes.insert(num);
			}
		}
	}

	return primes;
}