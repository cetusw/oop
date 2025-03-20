#include "HTMLDecoder.h"
#include "HTMLDecoderUtils.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

std::string ReadHTMLEntity(const std::string &inputString, size_t &position)
{
    std::string entity;

    while (position < inputString.length() &&
           std::isalpha(static_cast<unsigned char>(inputString[position])))
    {
        entity += inputString[position];
        position++;
    }

    if (position >= inputString.length() || inputString[position] != ';')
    {
        return "&" + entity;
    }

    position++;
    return entity;
}

std::string GetHTMLEntity(const std::string &stringEntity)
{
    const auto entity = HTMLEntityMap.find(stringEntity);
    if (entity != HTMLEntityMap.end())
    {
        return entity->second;
    }
    return "&" + stringEntity + ";";
}

std::string DecodeString(const std::string &inputString)
{
    size_t position = 0;
    std::string result;

    while (position < inputString.length())
    {
        const size_t foundPosition = inputString.find('&', position);

        if (foundPosition == std::string::npos)
        {
            result += inputString.substr(position);
            break;
        }

        result += inputString.substr(position, foundPosition - position);
        position = foundPosition + 1;

        std::string stringEntity = ReadHTMLEntity(inputString, position);
        if (stringEntity[0] != '&')
        {
        	result += GetHTMLEntity(stringEntity);
        	continue;
        }
    	result += stringEntity;
    }

    return result;
}

void CopyWithDecoding(std::istream &inputFile, std::ostream &outputFile)
{
    std::string line;

    while (std::getline(inputFile, line))
    {
        outputFile << DecodeString(line) << "\n";
    }
}

int HTMLDecode(const std::string &inputPath, const std::string &outputPath)
{
    auto inputFile = std::ifstream(inputPath);
    auto outputFile = std::ofstream(outputPath);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        throw std::runtime_error("ERROR");
    }

    CopyWithDecoding(inputFile, outputFile);

    return 0;
}
