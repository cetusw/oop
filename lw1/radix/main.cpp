#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ranges>

void PrintHelp()
{
	auto helpFile = std::ifstream("../utils/help.txt");
	std::string line;
	if (!helpFile.is_open())
	{
		std::cerr << "ERROR" << std::endl;
		return;
	}
	while (std::getline(helpFile, line))
	{
		std::cout << line << std::endl;
	}
}

bool isStringNumber(const std::string& str)
{
	return std::ranges::all_of(str, ::isdigit);
}

int CharToInt(const char ch)
{
	int digit = 0;
	if (isdigit(ch))
	{
		digit = ch - '0';
	}
	else if (isalpha(ch))
	{
		digit = toupper(ch) - 'A' + 10;
	}

	return digit;
}

bool isRadixValid(const int radix)
{
	if (radix < 2 || radix > 36)
	{
		return false;
	}
	return true;
}

int StringToInt(const std::string& value, const int radix, bool& wasError)
{
	if (!isRadixValid(radix))
	{
		wasError = true;
		return 1;
	}

	bool isNegative = false;
	int startIndex = 0;
	if (value[0] == '-')
	{
		isNegative = true;
		startIndex = 1;
	}

	int result = 0;
	for (; startIndex < value.size(); startIndex++)
	{
		const int digit = CharToInt(value[startIndex]);

		if (digit < 0 || digit >= radix)
		{
			wasError = true;
			return 1;
		}

		if (result > (std::numeric_limits<int>::max() - digit) / radix)
		{
			wasError = true;
			return 1;
		}

		result = result * radix + digit;
	}

	return isNegative ? -result : result;
}

std::string IntToNewNotation(int decimal, const int radix)
{
	std::string number;
	while (decimal > 0)
	{
		if (const int digit = decimal % radix; digit < 10)
		{
			number += static_cast<char>(digit + '0');
		}
		else
		{
			number += static_cast<char>(digit - 10 + 'A');
		}

		decimal /= radix;
	}

	return number;
}

std::string IntToString(int decimal, const int radix, bool& wasError)
{
	bool isNegative = false;

	if (!isRadixValid(radix))
	{
		wasError = true;
		return "";
	}

	if (decimal == 0)
	{
		return "0";
	}

	if (decimal < 0)
	{
		isNegative = true;
		decimal = -decimal;
	}

	std::string result = IntToNewNotation(decimal, radix);

	if (isNegative)
	{
		result += '-';
	}

	std::ranges::reverse(result);
	return result;
}

int main(const int argc, char* argv[])
{
	if (argc == 2 && std::strcmp(argv[1], "-h") == 0)
	{
		PrintHelp();
		return 0;
	}
	if (argc != 4)
	{
		std::cerr << "ERROR" << std::endl;
		return 0;
	}

	if (!isStringNumber(argv[1]) || !isStringNumber(argv[2]))
	{
		std::cerr << "ERROR" << std::endl;
		return 0;
	}

	const int initialRadix = std::stoi(argv[1]);
	const int finalRadix = std::stoi(argv[2]);
	const std::string initialValue = argv[3];
	bool wasError = false;

	const int decimalNumber = StringToInt(initialValue, initialRadix, wasError);
	if (wasError)
	{
		std::cerr << "ERROR" << std::endl;
		return 0;
	}

	const std::string newValue = IntToString(decimalNumber, finalRadix, wasError);
	if (wasError)
	{
		std::cerr << "ERROR" << std::endl;
		return 0;
	}

	std::cout << newValue << std::endl;
	return 1;
}
