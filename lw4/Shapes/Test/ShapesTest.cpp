#include "../Controller/ShapeController.h"
#include "../Shape/Circle.h"
#include "../Shape/LineSegment.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Triangle.h"

#include <gtest/gtest.h>

// EXPECT_EQ(shape.ToString(),
// 	"Area: " + std::to_string(area) + "\n" + "Perimetr: " + std::to_string(perimeter) + "\n"
// 		+ "OutlineColor: " + std::to_string(outlineColor + "\n" + "FillColor: " + fillColor + "\n");

uint32_t StringToUint32(const std::string& string)
{
	if (string.length() != 6)
	{
		throw std::invalid_argument("Invalid color string");
	}

	return std::stoul(string, nullptr, 16);
}

void ShapeTest(std::stringstream& ss)
{
	ShapeController shapeController(ss);
	shapeController.ReadShapes();
	shapeController.PrintBiggestAreaShape();
	shapeController.PrintShortestPerimeterShape();
}

void CircleTest(const Point center, const double radius, const uint32_t outlineColor,
	const uint32_t fillColor, const double perimeter, const double area,
	const std::string& expectedException = "")
{
	if (!expectedException.empty())
	{
		EXPECT_THROW(
			{ Circle shape(center, radius, outlineColor, fillColor); }, std::invalid_argument);
		return;
	}
	auto shape = Circle(center, radius, outlineColor, fillColor);
	EXPECT_EQ(shape.GetOutlineColor(), outlineColor);
	EXPECT_EQ(shape.GetFillColor(), fillColor);
	EXPECT_EQ(shape.GetArea(), area);
	EXPECT_NEAR(shape.GetPerimeter(), perimeter, 0.01);
	EXPECT_EQ(shape.GetCenter(), center);
	EXPECT_NEAR(shape.GetRadius(), radius, 0.01);
}

void LineSegmentTest(const Point startPoint, const Point endPoint, const uint32_t outlineColor,
	const double perimeter, const double area)
{
	auto shape = LineSegment(startPoint, endPoint, outlineColor);
	EXPECT_EQ(shape.GetStartPoint(), startPoint);
	EXPECT_EQ(shape.GetEndPoint(), endPoint);
	EXPECT_EQ(shape.GetOutlineColor(), outlineColor);
	EXPECT_EQ(shape.GetArea(), area);
	EXPECT_NEAR(shape.GetPerimeter(), perimeter, 0.01);
}

void RectangleTest(const Point leftTop, const Point rightBottom, const uint32_t outlineColor,
	const uint32_t fillColor, const double perimeter, const double area, const double width,
	const double height)
{
	auto shape = Rectangle(leftTop, rightBottom, outlineColor, fillColor);
	EXPECT_EQ(shape.GetWidth(), width);
	EXPECT_EQ(shape.GetHeight(), height);
	EXPECT_EQ(shape.GetLeftTop(), leftTop);
	EXPECT_EQ(shape.GetRightBottom(), rightBottom);
	EXPECT_EQ(shape.GetOutlineColor(), outlineColor);
	EXPECT_EQ(shape.GetFillColor(), fillColor);
	EXPECT_EQ(shape.GetArea(), area);
	EXPECT_NEAR(shape.GetPerimeter(), perimeter, 0.01);
}

void TriangleTest(const Point vertex1, const Point vertex2, const Point vertex3,
	const uint32_t outlineColor, const uint32_t fillColor, const double perimeter,
	const double area)
{
	auto shape = Triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);
	EXPECT_EQ(shape.GetVertex1(), vertex1);
	EXPECT_EQ(shape.GetVertex2(), vertex2);
	EXPECT_EQ(shape.GetVertex3(), vertex3);
	EXPECT_EQ(shape.GetOutlineColor(), outlineColor);
	EXPECT_EQ(shape.GetFillColor(), fillColor);
	EXPECT_EQ(shape.GetArea(), area);
	EXPECT_NEAR(shape.GetPerimeter(), perimeter, 0.01);
}

TEST(CircleTest, Zero) { CircleTest({ 0, 0 }, 0, 0x000000, 0x000000, 0, 0); }
TEST(CircleTest, NegativeRadius)
{
	CircleTest({ 0, 0 }, -1, 0x000000, 0x000000, 0, 0, "Radius cannot be negative");
}
TEST(CircleTest, Normal)
{
	CircleTest({ 50, 50 }, 50, 0x000000, 0x000000, 314.159265, 7853.981633974483);
}
TEST(CircleTest, NegativeCenter)
{
	CircleTest({ -50, -50 }, 50, 0x000000, 0x000000, 314.159265, 7853.981633974483);
}
TEST(CircleTest, NegativeAndPositiveCenter)
{
	CircleTest({ -50, 50 }, 50, 0x000000, 0x000000, 314.159265, 7853.981633974483);
}
TEST(CircleTest, PositiveAndNegativeCenter)
{
	CircleTest({ 50, -50 }, 50, 0x000000, 0x000000, 314.159265, 7853.981633974483);
}

TEST(LineSegmentTest, Zero) { LineSegmentTest({ 0, 0 }, { 0, 0 }, 0x000000, 0, 0); }
TEST(LineSegmentTest, Normal) { LineSegmentTest({ 1, 1 }, { 7, 9 }, 0x000000, 10, 10); }
TEST(LineSegmentTest, NegativePoints) { LineSegmentTest({ -4, -3 }, { 0, 0 }, 0x000000, 5, 5); }

TEST(RectangleTest, Zero) { RectangleTest({ 0, 0 }, { 0, 0 }, 0x000000, 0x000000, 0, 0, 0, 0); }
TEST(RectangleTest, Normal) { RectangleTest({ 0, 0 }, { 5, 5 }, 0x000000, 0x000000, 20, 25, 5, 5); }
TEST(RectangleTest, NegativePoints)
{
	RectangleTest({ -4, -3 }, { 0, 0 }, 0x000000, 0x000000, 14, 12, 3, 4);
}

TEST(TriangleTest, Zero) { TriangleTest({ 0, 0 }, { 0, 0 }, { 0, 0 }, 0x000000, 0x000000, 0, 0); }
TEST(TriangleTest, Rect) { TriangleTest({ 0, 0 }, { 3, 4 }, { 3, 0 }, 0x000000, 0x000000, 12, 6); }
TEST(TriangleTest, Isosceles) { TriangleTest({ 0, 3 }, { 4, 6 }, { 4, 0 }, 0x000000, 0x000000, 16, 12); }
TEST(TriangleTest, Equilateral) { TriangleTest({ 0, 5 }, { 8.660254037844386, 10 }, { 8.660254037844386, 0 }, 0x000000, 0x000000, 30, 43.301270189221924); }