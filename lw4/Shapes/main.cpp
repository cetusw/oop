#include "Controller/ShapeController.h"

#include <fstream>

int main()
{
	ShapeController shapeController(std::cin);
	shapeController.ReadShapes();
	shapeController.PrintBiggestAreaShape();
	shapeController.PrintShortestPerimeterShape();
}