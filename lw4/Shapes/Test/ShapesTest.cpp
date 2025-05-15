#include "../Controller/ShapeController.h"
#include <gtest/gtest.h>

void ShapeTest(std::stringstream& ss)
{
	ShapeController shapeController(ss);
	shapeController.ReadShapes();
	shapeController.PrintBiggestAreaShape();
	shapeController.PrintShortestPerimeterShape();
}