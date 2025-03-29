#ifndef DICTIONARYUTILS_H
#define DICTIONARYUTILS_H
#include "DictionaryTypes.h"

#include <string>

bool IsAvailableForKey(const std::string& word);

bool isEntryExists(const Dictionary& dict, const std::string& newKey, const std::string& newValue);

std::string StringToLower(const std::string& str);

void AddToDictionary(Dictionary& dict, const std::string& key, const std::string& value);

std::set<std::string> SplitString(std::string input, char delimiter);

void ProcessUnknownInput(const std::string& input, Dictionary& enRuDict, Dictionary& ruEnDict,
	const bool& isEng, bool& modified);

void ProcessRussianInput(const std::string& input, Dictionary& ruEnDict, bool& found);

void ProcessEnglishInput(const std::string& input, Dictionary& enRuDict, bool& found);



#endif //DICTIONARYUTILS_H
