#include "Dictionary.h"
#include "DictionaryUtils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

void PrintResponse(std::stringstream& ss)
{
	std::string line;
	while (std::getline(ss, line))
	{
		std::cout << line << std::endl;
	}
}

bool IsAvailableForKey(const std::string& word)
{
	return std::ranges::all_of(
		word, [](const char c) { return std::isalpha(c) || c == ' ' || c == '\'' || c == '-'; });
}

std::string StringToLower(const std::string& str)
{
	std::string result;
	for (const char ch : str)
	{
		result += static_cast<char>(std::tolower(ch));
	}
	return result;
}

void AddToDictionary(Dictionary& dict, const std::string& key, const std::string& value)
{
	auto& entries = dict[key];
	entries.insert(value);
}

void ProcessInput(
	const std::string& input, Dictionary& dictionary, bool& found, std::stringstream& outputStream)
{
	outputStream.clear();
	const std::string lowerInput = StringToLower(input);
	const auto record = dictionary.find(lowerInput);
	if (record != dictionary.end())
	{
		auto it = record->second.begin();
		while (it != record->second.end())
		{
			outputStream << *it;
			++it;
			if (it != record->second.end())
			{
				outputStream << ", ";
			}
		}
		found = true;
	}
	PrintResponse(outputStream);
}

std::set<std::string> SplitString(std::string input, const char delimiter)
{
	std::set<std::string> result;

	while (input.find(delimiter) != std::string::npos)
	{
		result.insert(input.substr(0, input.find(delimiter)));
		input.erase(0, input.find(delimiter) + 2);
	}
	result.insert(input);

	return result;
}

void ProcessUnknownInput(const std::string& input, Dictionary& enRuDict, Dictionary& ruEnDict,
	const bool& isEng, bool& modified, std::stringstream& outputStream, std::istream& inputStream)
{
	outputStream.clear();
	outputStream << "Неизвестное слово \"" << input
				 << "\". Введите перевод или пустую строку для отказа." << std::endl;
	PrintResponse(outputStream);

	std::string translation;
	getline(inputStream, translation);
	if (translation.empty())
	{
		outputStream.clear();
		outputStream << "Слово \"" << input << "\" проигнорировано." << std::endl;
		PrintResponse(outputStream);
		return;
	}

	std::string key;
	const std::set<std::string> values = SplitString(translation, ',');
	if (isEng)
	{
		key = StringToLower(input);
		for (const auto& value : values)
		{
			AddToDictionary(enRuDict, key, value);
			AddToDictionary(ruEnDict, value, key);
		}
	}
	else
	{
		key = input;
		AddToDictionary(ruEnDict, key, translation);
		AddToDictionary(enRuDict, translation, key);
	}
	modified = true;
	std::string finalTranslation;
	bool isFirst = true;

	for (const auto& value : values)
	{
		if (!isFirst)
		{
			finalTranslation += ", ";
		}
		else
		{
			isFirst = false;
		}
		finalTranslation += value;
	}

	outputStream.clear();
	outputStream << "Слово \"" << input << "\" сохранено в словаре как \"" << finalTranslation
				 << "\"." << std::endl;
	PrintResponse(outputStream);
}

void Translate(const std::string& input, Dictionary& enRuDict, Dictionary& ruEnDict, bool& modified,
	std::stringstream& outputStream, std::istream& inputStream)
{
	const bool isEng = IsAvailableForKey(input);
	bool wordFound = false;

	if (isEng)
	{
		ProcessInput(input, enRuDict, wordFound, outputStream);
		if (wordFound)
		{
			return;
		}
	}

	ProcessInput(input, ruEnDict, wordFound, outputStream);
	if (wordFound)
	{
		return;
	}

	ProcessUnknownInput(input, enRuDict, ruEnDict, isEng, modified, outputStream, inputStream);
}

bool isEntryExists(const Dictionary& dict, const std::string& newKey, const std::string& newValue)
{
	const auto key = dict.find(newKey);
	if (key != dict.end())
	{
		const auto& values = key->second;
		return std::ranges::find(values, newValue) != values.end();
	}
	return false;
}

bool LoadDictionary(const std::string& filename, Dictionary& enRuDict, Dictionary& ruEnDict)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::invalid_argument("ERROR");
	}

	std::string line;
	while (getline(file, line))
	{
		size_t tabPos = line.find('*');
		if (tabPos == std::string::npos)
		{
			continue;
		}

		std::string key = line.substr(0, tabPos);
		std::string value = line.substr(tabPos + 1);

		if (IsAvailableForKey(key))
		{
			if (!isEntryExists(enRuDict, key, value))
			{
				AddToDictionary(enRuDict, key, value);
				AddToDictionary(ruEnDict, value, key);
			}
		}
		else
		{
			if (!isEntryExists(ruEnDict, key, value))
			{
				AddToDictionary(ruEnDict, key, value);
				AddToDictionary(enRuDict, value, key);
			}
		}
	}
	return true;
}

void SaveDictionary(const std::string& filename, const Dictionary& enRuDict)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		throw std::invalid_argument("ERROR");
	}

	for (const auto& pair : enRuDict)
	{
		for (const std::string& value : pair.second)
		{
			file << pair.first << '*' << value << '\n';
		}
	}
}
