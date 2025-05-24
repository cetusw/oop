#include "FindMaxEx.h"
#include "Sportsman.h"

#include <iostream>
#include <vector>

int main()
{
	std::vector<Sportsman> sportsmen;
	sportsmen.push_back({
		"Sportsman1", 160.1, 100.3
	});
	sportsmen.push_back({
		"Sportsman2", 180.9, 80.5
	});

	Sportsman highestSportsman;
	Sportsman heaviestSportsman;
	auto returnHighest = [](const Sportsman& a, const Sportsman& b) { return a.height < b.height; };
	auto returnHeaviest = [](const Sportsman& a, const Sportsman& b) { return a.weight < b.weight; };
	FindMaxEx<Sportsman>(sportsmen, highestSportsman, returnHighest);
	FindMaxEx<Sportsman>(sportsmen, heaviestSportsman, returnHeaviest);

	std::cout << "Самый высокий спортсмен: " << highestSportsman.name << " - " << highestSportsman.height << "см" << std::endl;
	std::cout << "Самый тяжёлый спортсмен: " << heaviestSportsman.name << " - " << heaviestSportsman.weight << "кг" << std::endl;

}
