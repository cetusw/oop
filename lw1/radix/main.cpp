#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ranges>

void printHelp()
{
	auto helpFile = std::ifstream("../utils/help.txt");
	std::string line;
	while (std::getline(helpFile, line))
	{
		std::cout << line << std::endl;
	}
}

bool isNegativeString(const std::string& number) { return number[0] == '-'; }

int StringToInt(const std::string& value, const int radix, bool& wasError)
{
	if (radix < 2 || radix > 36)
	{
		wasError = true;
		return 1;
	}

	int result = 0;
	int degree = 0;
	for (int i = static_cast<int>(value.length()) - 1; i >= 0; i--)
	{
		int digit = 0;
		if (isdigit(value[i]))
		{
			digit = value[i] - '0';
		}
		else if (isalpha(value[i]))
		{
			digit = toupper(value[i]) - 'A' + 10;
		}

		if (digit < 0 || digit >= radix)
		{
			wasError = true;
			return 1;
		}

		result += digit * static_cast<int>(pow(radix, degree));
		degree++;
	}

	return isNegativeString(value) ? -result : result;
}

std::string IntToString(int decimal, const int radix, bool& wasError)
{
	std::string result;
	bool isNegative = false;

	if (radix < 2 || radix > 36)
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

	while (decimal > 0)
	{
		const int digit = decimal % radix;
		if (digit < 10)
		{
			result += static_cast<char>(digit + '0');
		}
		else
		{
			result += static_cast<char>(digit - 10 + 'A');
		}

		decimal /= radix;
	}

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
		printHelp();
		return 0;
	}
	if (argc != 4)
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
