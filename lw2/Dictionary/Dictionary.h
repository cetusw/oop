#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <unordered_map>
#include <vector>

#include "DictionaryTypes.h"

void Translate(
	const std::string& input, Dictionary& enRuDict, Dictionary& ruEnDict, bool& modified);

bool LoadDictionary(const std::string& filename, Dictionary& enRuDict, Dictionary& ruEnDict);

void SaveDictionary(const std::string& filename, const Dictionary& enRuDict);

#endif // DICTIONARY_H
