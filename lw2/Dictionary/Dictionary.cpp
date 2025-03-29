#include "Dictionary.h"
#include "DictionaryUtils.h"

#include <algorithm>
#include <fstream>
#include <iostream>

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

void ProcessRussianInput(const std::string& input, Dictionary& ruEnDict, bool& found)
{
	const std::string lowerInput = StringToLower(input);
	const auto record = ruEnDict.find(lowerInput);
	if (record != ruEnDict.end())
	{
		auto it = record->second.begin();
		while (it != record->second.end())
		{
			std::cout << *it;
			++it;
			if (it != record->second.end())
			{
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
		found = true;
	}
}

void ProcessEnglishInput(const std::string& input, Dictionary& enRuDict, bool& found)
{
	const std::string lowerInput = StringToLower(input);
	const auto record = enRuDict.find(lowerInput);
	if (record != enRuDict.end())
	{
		auto it = record->second.begin();
		while (it != record->second.end())
		{
			std::cout << *it;
			++it;
			if (it != record->second.end())
			{
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
		found = true;
	}
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
	const bool& isEng, bool& modified)
{
	std::cout << "Неизвестное слово \"" << input
			  << "\". Введите перевод или пустую строку для отказа." << std::endl;

	std::string translation;
	getline(std::cin, translation);
	if (translation.empty())
	{
		std::cout << "Слово \"" << input << "\" проигнорировано." << std::endl;
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

	std::cout << "Слово \"" << input << "\" сохранено в словаре как \"" << finalTranslation << "\"."
			  << std::endl;
}

void Translate(const std::string& input, Dictionary& enRuDict, Dictionary& ruEnDict,
	bool& modified) // добавить stdout
{
	const bool isEng = IsAvailableForKey(input);
	bool wordFound = false;

	if (isEng)
	{
		ProcessEnglishInput(input, enRuDict, wordFound);
		if (wordFound)
		{
			return;
		}
	}

	ProcessRussianInput(input, ruEnDict, wordFound);
	if (wordFound)
	{
		return;
	}

	ProcessUnknownInput(input, enRuDict, ruEnDict, isEng, modified);
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
