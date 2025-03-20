//
// Created by cetus on 3/15/25.
//

#ifndef HTMLDECODERUTILS_H
#define HTMLDECODERUTILS_H

#include <map>

std::string ReadHTMLEntity(const std::string &inputString, size_t &position);
std::string GetHTMLEntity(const std::string &inputString, size_t foundPosition, size_t &position);
std::string DecodeString(const std::string &inputString);
void CopyWithDecoding(std::istream &inputFile, std::ostream &outputFile);

const std::map<std::string, std::string> HTMLEntityMap = {
    {"quot", "\""},
    {"apos", "'"},
    {"lt", "<"},
    {"gt", ">"},
    {"amp", "&"}
};

#endif //HTMLDECODERUTILS_H
