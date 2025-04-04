#include "Dictionary.h"

#include <fstream>
#include <iostream>
#include <sstream>

int main(const int argc, char* argv[])
{
	try
	{
		if (argc == 2)
		{
			std::string input;
			std::stringstream output;
			bool modified = false;
			Dictionary enRuDict;
			Dictionary ruEnDict;
			do
			{
				LoadDictionary(argv[1], enRuDict, ruEnDict);
				getline(std::cin, input);
				if (input == "...")
				{
					if (modified)
					{
						std::cout << "В словарь были внесены изменения. Введите Y или y для "
									 "сохранения перед выходом."
								  << std::endl;
						char answer;
						std::cin >> answer;
						if (answer == 'y' || answer == 'Y')
						{
							SaveDictionary(argv[1], enRuDict);
						}
					}
					break;
				}
				Translate(input, enRuDict, ruEnDict, modified, output, std::cin);
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
