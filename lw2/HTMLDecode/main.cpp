#include <iostream>
#include <ostream>
#include <string>
#include <fstream>

enum class HTMLEntity
{
    Quote,
    Apostrophe,
    LessThan,
    GreaterThan,
    Ampersand,
    Unknown,
};

std::string GetHTMLEntity(const std::string &inputString, const size_t foundPosition, size_t &position)
{
    std::string result;
    size_t currentPosition = foundPosition + 1;
    while (inputString[currentPosition] != ' ')
    {
        result.append(1, inputString[currentPosition]);
        currentPosition++;
    }
    position = currentPosition;

    if (result == "quot")
    {
        return"\"";
    }
    if (result == "apos")
    {
        return"'";
    }
    if (result == "lt")
    {
        return "<";
    }
    if (result == "gt")
    {
        return ">";
    }
    if (result == "amp")
    {
        std::cout << result << " ";
        return "&";
    }
    return ;
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
            result.append(inputString, position, inputString.length() - position);
            break;
        }

        std::string replacementString = GetHTMLEntity(inputString, foundPosition, position);

        result.append(inputString, position, foundPosition - position);
        result.append(replacementString);
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

int ProcessDecoding(const std::string &inputPath, const std::string &outputPath)
{
    auto inputFile = std::ifstream(inputPath);
    auto outputFile = std::ofstream(outputPath);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cout << "ERROR" << std::endl;
        return 1;
    }

    CopyWithDecoding(inputFile, outputFile);

    return 0;
}

int main(const int argc, char *argv[])
{
    try
    {
        if (argc == 3)
        {
            ProcessDecoding(argv[1], argv[2]);
        } else
        {
            throw std::invalid_argument("ERROR");
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
