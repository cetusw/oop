#include "Dictionary.h"

#include <iostream>
#include <stdexcept>

int main(const int argc, char* argv[])
{
	try
	{
		if (argc == 2)
		{
			std::string input;
			bool modified = false;
			Dictionary enRuDict;
			Dictionary ruEnDict;
			do
			{
				LoadDictionary(argv[1], enRuDict, ruEnDict);
				getline(std::cin, input);
				if (input == "...")
				{
					break;
				}
				ProcessInput(input, enRuDict, ruEnDict, modified);
			} while (true);
			if (modified)
			{
				SaveDictionary(argv[1], enRuDict);
			}
		}
		else
		{
			throw std::invalid_argument("ERROR");
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
