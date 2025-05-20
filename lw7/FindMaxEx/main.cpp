#include "FindMaxEx.h"
#include "Sportsman.h"

#include <iostream>
#include <vector>

int main()
{
	std::vector<Sportsman> sportsmen;
	sportsmen.push_back({
		"Sportsman1", "Sportsman1", "Sportsman1", 179.0, 180.0
	});
	sportsmen.push_back({
		"Sportsman2", "Sportsman2", "Sportsman2", 180.0, 180.0
	});
	Sportsman maxHeight;
	auto lessByHeight = [](const Sportsman& a, const Sportsman& b) { return a.height > b.height; };
	FindMaxEx<Sportsman>(sportsmen, maxHeight, lessByHeight);

	std::cout << maxHeight.name << std::endl;
}
