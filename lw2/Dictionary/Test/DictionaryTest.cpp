#include "../Dictionary.h"
#include "../DictionaryTypes.h"
#include "catch2/catch_all.hpp"
#include <fstream>

#include <iostream>

struct TestData
{
	Dictionary enRuDict = {
		{ "cat", { "кот", "кошка" } },
		{ "dog", { "собака" } },
		{ "The Red Square", { "Красная Площадь" } },
	};

	Dictionary ruEnDict = {
		{ "кот", { "cat" } },
		{ "кошка", { "cat" } },
		{ "собака", { "dog" } },
		{ "Красная Площадь", { "The Red Square" } },
	};
};

void ProcessInputTest(const std::string& testString, const std::string& expectedString,
	const std::string& description, const std::string& translation = "")
{
	SECTION(description)
	{
		TestData testData;
		bool modified = false;

		std::streambuf* origCout = std::cout.rdbuf();
		std::streambuf* origCin = std::cin.rdbuf();
		std::stringstream outputBuffer;
		std::stringstream inputBuffer(translation);

		std::cout.rdbuf(outputBuffer.rdbuf());
		std::cin.rdbuf(inputBuffer.rdbuf());

		ProcessInput(testString, testData.enRuDict, testData.ruEnDict, modified);

		std::cout.rdbuf(origCout);
		std::cin.rdbuf(origCin);

		std::string actualOutput = outputBuffer.str();
		if (!actualOutput.empty() && actualOutput.back() == '\n')
		{
			actualOutput.pop_back();
		}

		REQUIRE(actualOutput == expectedString);
		if (modified)
		{
			REQUIRE(testData.enRuDict[testString] == std::vector<std::string>{SplitString(translation, ',')});
			for (const auto& item : SplitString(translation, ','))
			{
				REQUIRE(testData.ruEnDict[item] == std::vector<std::string>{testString});
			}
		}
	}
}

TEST_CASE("ProcessInput tests")
{
	ProcessInputTest("cat", "кот, кошка", "Прямой перевод с несколькими вариантами");

	ProcessInputTest("dog", "собака", "Прямой перевод с одним вариантом");

	ProcessInputTest("кот", "cat", "Обратный перевод");

	ProcessInputTest("apple",
		"Неизвестное слово \"apple\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"apple\" сохранено в словаре как \"яблоко\".",
		"Добавление нового слова", "яблоко");

	ProcessInputTest("unknown",
		"Неизвестное слово \"unknown\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"unknown\" проигнорировано.",
		"Игнорирование неизвестного слова", "");

	ProcessInputTest("CAT", "кот, кошка", "Поиск в верхнем регистре");

	ProcessInputTest("bottle of water",
		"Неизвестное слово \"bottle of water\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"bottle of water\" сохранено в словаре как \"бутылка воды\".",
		"Добавление составного выражения", "бутылка воды");

	ProcessInputTest("test",
		"Неизвестное слово \"test\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"test\" сохранено в словаре как \"тест, испытание\".",
		"Добавление нескольких переводов", "тест, испытание");

	ProcessInputTest("same",
		"Неизвестное слово \"same\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"same\" сохранено в словаре как \"same\".",
		"Слово и перевод идентичны", "same");

}
