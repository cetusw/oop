#include "../Dictionary.h"
#include "../DictionaryTypes.h"
#include "../DictionaryUtils.h"
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

		std::stringstream ss;
		std::istringstream inputStream(translation);

		Translate(testString, testData.enRuDict, testData.ruEnDict, modified, ss, inputStream);

		REQUIRE(ss.str() == expectedString);
		if (modified)
		{
			REQUIRE(testData.enRuDict[testString] == std::set<std::string>{SplitString(translation, ',')});
			for (const auto& item : SplitString(translation, ','))
			{
				REQUIRE(testData.ruEnDict[item] == std::set<std::string>{testString});
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
		"Слово \"apple\" сохранено в словаре как \"яблоко\".\n",
		"Добавление нового слова", "яблоко");

	ProcessInputTest("unknown",
		"Неизвестное слово \"unknown\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"unknown\" проигнорировано.\n",
		"Игнорирование неизвестного слова", "");

	ProcessInputTest("CAT", "кот, кошка", "Поиск в верхнем регистре");

	ProcessInputTest("bottle of water",
		"Неизвестное слово \"bottle of water\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"bottle of water\" сохранено в словаре как \"бутылка воды\".\n",
		"Добавление составного выражения", "бутылка воды");

	ProcessInputTest("test",
		"Неизвестное слово \"test\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"test\" сохранено в словаре как \"испытание, тест\".\n",
		"Добавление нескольких переводов", "испытание, тест");

	ProcessInputTest("same",
		"Неизвестное слово \"same\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"same\" сохранено в словаре как \"same\".\n",
		"Слово и перевод идентичны", "same");

	ProcessInputTest("",
		"Неизвестное слово \"\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"\" сохранено в словаре как \"пустая строка\".\n",
		"Пустая строка", "пустая строка");

	ProcessInputTest("test",
		"Неизвестное слово \"test\". Введите перевод или пустую строку для отказа.\n"
		"Слово \"test\" сохранено в словаре как \"тест\".\n",
		"Два одинаковых слова в переводе", "тест, тест");

}
