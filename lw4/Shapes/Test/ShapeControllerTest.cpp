#include "../Controller/ShapeController.h"
#include <cmath>
#include <gtest/gtest.h>

void PrintBiggestAreaShapeTest(std::stringstream& ss, const double expectedArea,
	const double expectedPerimeter, const std::string& expectedOutlineColor,
	const std::string& expectedFillColor = "")
{
	ShapeController shapeController(ss);
	std::string fillColorInfo;
	shapeController.ReadShapes();

	if (!expectedFillColor.empty())
	{
		fillColorInfo = "FillColor: " + expectedFillColor + "\n";
	}

	EXPECT_EQ(shapeController.PrintBiggestAreaShape(),
		"Area: " + std::to_string(expectedArea) + "\n"
			+ "Perimetr: " + std::to_string(expectedPerimeter) + "\n"
			+ "OutlineColor: " + expectedOutlineColor + "\n" + fillColorInfo);
}

void PrintShortestPerimeterShapeTest(std::stringstream& ss, const double expectedArea,
	const double expectedPerimeter, const std::string& expectedOutlineColor,
	const std::string& expectedFillColor = "")
{
	ShapeController shapeController(ss);
	std::string fillColorInfo;
	shapeController.ReadShapes();

	if (!expectedFillColor.empty())
	{
		fillColorInfo = "FillColor: " + expectedFillColor + "\n";
	}

	EXPECT_EQ(shapeController.PrintShortestPerimeterShape(),
		"Area: " + std::to_string(expectedArea) + "\n"
			+ "Perimetr: " + std::to_string(expectedPerimeter) + "\n"
			+ "OutlineColor: " + expectedOutlineColor + "\n" + fillColorInfo);
}

TEST(ShapeControllerTest, CircleArea)
{
	std::stringstream ss("circle 0 0 10 ff0000 00ff00");
	PrintBiggestAreaShapeTest(ss, M_PI * 10 * 10, 2 * M_PI * 10, "FF0000", "00FF00");
}

TEST(ShapeControllerTest, CirclePerimetr)
{
	std::stringstream ss("circle 0 0 10 ff0000 00ff00");
	PrintShortestPerimeterShapeTest(ss, M_PI * 10 * 10, 2 * M_PI * 10, "FF0000", "00FF00");
}

TEST(ShapeControllerTest, LineArea)
{
	std::stringstream ss("line 0 0 10 0 000000");
	PrintBiggestAreaShapeTest(ss, 10, 10, "000000");
}

TEST(ShapeControllerTest, LinePerimeter)
{
	std::stringstream ss("line 0 0 10 0 000000");
	PrintShortestPerimeterShapeTest(ss, 10, 10, "000000");
}

TEST(ShapeControllerTest, RectangleArea)
{
	std::stringstream ss("rectangle 0 0 5 10 ff0000 00ff00");
	PrintBiggestAreaShapeTest(ss, 50, 30, "FF0000", "00FF00");
}

TEST(ShapeControllerTest, RectanglePerimetr)
{
	std::stringstream ss("rectangle 0 0 5 10 ff0000 00ff00");
	PrintShortestPerimeterShapeTest(ss, 50, 30, "FF0000", "00FF00");
}

TEST(ShapeControllerTest, TriangleArea)
{
	std::stringstream ss("triangle 0 0 0 3 4 0 00ff00 ff0000");
	PrintBiggestAreaShapeTest(ss, 6, 12, "00FF00", "FF0000");
}

TEST(ShapeControllerTest, TrianglePerimetr)
{
	std::stringstream ss("triangle 0 0 0 3 4 0 00ff00 ff0000");
	PrintShortestPerimeterShapeTest(ss, 6, 12, "00FF00", "FF0000");
}

TEST(ShapeControllerTest, RectangleAndTriangleAreas)
{
	std::stringstream ss;
	ss << "rectangle 0 0 5 10 ff0000 00ff00\n"
	   << "triangle 0 0 0 3 4 0 00ff00 ff0000";
	PrintBiggestAreaShapeTest(ss, 50, 30, "FF0000", "00FF00");
}

TEST(ShapeControllerTest, RectangleAndTrianglePerimeters)
{
	std::stringstream ss;
	ss << "rectangle 0 0 5 10 ff0000 00ff00\n"
	   << "triangle 0 0 0 3 4 0 00ff00 ff0000";
	PrintShortestPerimeterShapeTest(ss, 6, 12, "00FF00", "FF0000");
}

TEST(ShapeControllerTest, CirclesArea)
{
	std::stringstream ss;
	ss << "circle 0 0 5 000000 000000\n"
	   << "circle 0 0 10 000000 000000\n"
	   << "circle 0 0 15 000000 000000";
	PrintBiggestAreaShapeTest(ss, M_PI * 225, 2 * M_PI * 15, "000000", "000000");
}

TEST(ShapeControllerTest, CirclesPerimetr)
{
	std::stringstream ss;
	ss << "circle 0 0 5 000000 000000\n"
	   << "circle 0 0 10 000000 000000\n"
	   << "circle 0 0 15 000000 000000";
	PrintShortestPerimeterShapeTest(ss, M_PI * 25, 2 * M_PI * 5, "000000", "000000");
}

TEST(ShapeControllerTest, LineAndCircleAreas)
{
	std::stringstream ss;
	ss << "line 0 0 30 0 000000\n"
	   << "circle 0 0 5 123456 789abc";
	PrintBiggestAreaShapeTest(ss, M_PI * 25, 2 * M_PI * 5, "123456", "789ABC");
}

TEST(ShapeControllerTest, LineAndCirclePerimetrs)
{
	std::stringstream ss;
	ss << "line 0 0 30 0 000000\n"
	   << "circle 0 0 5 123456 789abc";
	PrintShortestPerimeterShapeTest(ss, 30, 30, "000000");
}

TEST(ShapeControllerTest, EqualRectanglesArea)
{
	std::stringstream ss;
	ss << "rectangle 0 0 10 5 aaaaaa 111111\n"
	   << "rectangle 0 0 10 5 bbbbbb 222222";
	PrintBiggestAreaShapeTest(ss, 50, 30, "AAAAAA", "111111");
}

TEST(ShapeControllerTest, DegenerateTriangle)
{
	std::stringstream ss("triangle 0 0 0 5 0 3 777777 888888");
	PrintBiggestAreaShapeTest(ss, 0, 10, "777777", "888888");
}

TEST(ShapeControllerTest, AllShapesArea)
{
	std::stringstream ss;
	ss << "circle 0 0 5 111111 aaaaaa\n"
	   << "line 0 0 10 10 222222\n"
	   << "rectangle 10 10 20 30 333333 cccccc\n"
	   << "triangle 0 0 5 0 0 5 444444 dddddd";

	PrintBiggestAreaShapeTest(ss, 600.0, 2 * (20 + 30), "333333", "CCCCCC");
}

TEST(ShapeControllerTest, AllShapesPerimetr)
{
	std::stringstream ss;
	ss << "circle 0 0 5 111111 aaaaaa\n"
	   << "line 0 0 10 10 222222\n"
	   << "rectangle 10 10 20 30 333333 cccccc\n"
	   << "triangle 0 0 5 0 0 5 444444 dddddd";

	PrintShortestPerimeterShapeTest(ss, sqrt(200), sqrt(200), "222222");
}

TEST(ShapeControllerTest, ZeroSizeShapesArea)
{
	std::stringstream ss;
	ss << "circle 0 0 0 000000 000000\n"
	   << "rectangle 0 0 0 0 111111 111111";
	PrintBiggestAreaShapeTest(ss, 0.0, 0.0, "000000", "000000");
}

TEST(ShapeControllerTest, ZeroSizeShapesPerimetr)
{
	std::stringstream ss;
	ss << "circle 0 0 0 000000 000000\n"
	   << "rectangle 0 0 0 0 111111 111111";
	PrintShortestPerimeterShapeTest(ss, 0.0, 0.0, "000000", "000000");
}
