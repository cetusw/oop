#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

void printHelp()
{
	auto helpFile = std::ifstream("../utils/help.txt");
	std::string line;
	while (std::getline(helpFile, line))
	{
		std::cout << line << std::endl;
	}
}

void resetOccurrence(std::string& occurrence, int& index)
{
	occurrence.clear();
	index = 0;
}

std::string ReplaceString(const std::string& inputString, const std::string& searchString,
	const std::string& replaceString)
{
	std::string result;
	std::string stringOccurrence;

	int i = 0;
	for (int j = 0; j < inputString.length(); j++)
	{
		if (inputString[j] == searchString[i])
		{
			stringOccurrence += inputString[j];
			i++;
			if (i == searchString.length())
			{
				result += replaceString;
				resetOccurrence(stringOccurrence, i);
			}
			continue;
		}
		if (!stringOccurrence.empty())
		{
			j -= static_cast<int>(stringOccurrence.length());
			result += inputString[j];
			resetOccurrence(stringOccurrence, i);
			continue;
		}
		result += inputString[j];
	}

	return result;
}

void CopyFileWithReplacement(std::ifstream& inputFile, std::ofstream& outputFile,
	const std::string& searchString, const std::string& replaceString)
{
	std::string line;

	while (std::getline(inputFile, line))
	{
		outputFile << ReplaceString(line, searchString, replaceString) << "\n";
	}
}

int processFileMode(const char* inputPath, const char* outputPath, const std::string& search,
	const std::string& replace)
{
	auto inputFile = std::ifstream(inputPath);
	auto outputFile = std::ofstream(outputPath);
	auto searchString = std::string(search);
	auto replaceString = std::string(replace);

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	CopyFileWithReplacement(inputFile, outputFile, searchString, replaceString);

	return 0;
}

int processStdinMode()
{
	std::string searchString;
	std::string replaceString;
	std::string line;
	std::vector<std::string> input;

	if (!std::getline(std::cin, searchString) || !std::getline(std::cin, replaceString))
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	while (std::getline(std::cin, line))
	{
		input.emplace_back(line);
	}

	if (input.empty())
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	for (const auto& inputLine : input)
	{
		std::cout << ReplaceString(inputLine, searchString, replaceString) << "\n";
	}

	return 0;
}

int main(const int argc, char* argv[])
{
	if (argc == 2 && std::strcmp(argv[1], "-h") == 0)
	{
		printHelp();
		return 0;
	}
	if (argc == 5)
	{
		processFileMode(argv[1], argv[2], argv[3], argv[4]);
	}
	else if (argc == 1)
	{
		processStdinMode();
	}
	else
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}
}
