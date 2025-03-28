#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <unordered_map>
#include <vector>

#include "DictionaryTypes.h"

bool IsEnglish(const std::string& word);

std::string StringToLower(const std::string& str);

void AddToDictionary(Dictionary& dict, const std::string& key, const std::string& value);

std::vector<std::string> SplitString(std::string input, char delimiter);

void ProcessInput(
	const std::string& input, Dictionary& enRuDict, Dictionary& ruEnDict, bool& modified);

void ProcessUnknownInput(const std::string& input, Dictionary& enRuDict, Dictionary& ruEnDict,
	const bool& isEng, bool& modified);

bool LoadDictionary(const std::string& filename, Dictionary& enRuDict, Dictionary& ruEnDict);

void SaveDictionary(const std::string& filename, const Dictionary& enRuDict);

#endif // DICTIONARY_H
