#include "Controller/ShapeController.h"

#include <iostream>

int main()
{
	ShapeController shapeController(std::cin);
	shapeController.ReadShapes();
	shapeController.PrintBiggestAreaShape();
	shapeController.PrintShortestPerimeterShape();
}