#include "Canvas/Canvas.h"
#include "Controller/ShapeController.h"

#include <fstream>
#include <iostream>

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

int main()
{
	std::ifstream input("../Test/data/test.txt");
	if (!input.is_open())
	{
		std::cerr << "Failed to open file" << std::endl;
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	ShapeController shapeController(input);
	shapeController.ReadShapes();

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),
		"Shapes",
		sf::Style::Default, settings);

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::White);
		shapeController.DrawShapes(window);
		window.display();
	}

	shapeController.PrintBiggestAreaShape();
	shapeController.PrintShortestPerimeterShape();
}