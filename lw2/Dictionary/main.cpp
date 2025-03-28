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
					std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
					char answer;
					std::cin >> answer;
					if (modified && (answer == 'y' || answer == 'Y'))
					{
						SaveDictionary(argv[1], enRuDict);
					}
					break;
				}
				ProcessInput(input, enRuDict, ruEnDict, modified);
			} while (true);
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
