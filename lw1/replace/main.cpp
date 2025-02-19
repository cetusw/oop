#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

void PrintHelp()
{
	auto helpFile = std::ifstream("../utils/help.txt");
	std::string line;
	while (std::getline(helpFile, line))
	{
		std::cout << line << std::endl;
	}
}

void printFile(std::ifstream& file)
{
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}
	file.close();
}

void ResetOccurrence(std::string& occurrence, int& index)
{
	occurrence.clear();
	index = 0;
}

std::string ReplaceString(const std::string& inputString, const std::string& searchString,
	const std::string& replacementString)
{
	if (searchString.empty())
	{
		return inputString;
	}

	size_t position = 0;
	std::string result;

	while (position < inputString.length())
	{
		const size_t foundPosition = inputString.find(searchString, position);

		if (foundPosition == std::string::npos)
		{
			result.append(inputString, position, inputString.length() - position);
			break;
		}

		result.append(inputString, position, foundPosition - position);
		result.append(replacementString);
		position = foundPosition + searchString.length();
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

int processFileMode(const std::string& inputPath, const std::string& outputPath,
	const std::string& search, const std::string& replace)
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

	if (!std::getline(std::cin, searchString) || !std::getline(std::cin, replaceString))
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	std::ofstream outReplacedFile("../buf.txt");
	while (std::getline(std::cin, line))
	{
		outReplacedFile << ReplaceString(line, searchString, replaceString) << std::endl;
	}
	outReplacedFile.close();

	std::ifstream inReplacedFile("../buf.txt");
	printFile(inReplacedFile);

	return 0;
}

int main(const int argc, char* argv[])
{
	if (argc == 2 && std::strcmp(argv[1], "-h") == 0)
	{
		PrintHelp();
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
