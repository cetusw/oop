#include "ShapeController.h"

#include "../Shape/Circle.h"
#include "../Shape/LineSegment.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Triangle.h"

#include <bits/ranges_algo.h>
#include <iostream>
#include <ostream>
#include <stdexcept>

ShapeController::ShapeController(std::istream& input)
	: m_input(input)
{
	m_commands.emplace("circle", [this]() { AddCircle(); });
	m_commands.emplace("line", [this]() { AddLineSegment(); });
	m_commands.emplace("rectangle", [this]() { AddRectangle(); });
	m_commands.emplace("triangle", [this]() { AddTriangle(); });
}

void ShapeController::ReadShapes()
{
	std::string command;
	while (m_input >> command && command != "...")
	{
		const auto it = m_commands.find(command);
		if (it != m_commands.end())
		{
			try
			{
				it->second();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		else
		{
			std::cerr << "Command not found" << std::endl;
		}
		std::cout << command << std::endl;
	}
}

void ShapeController::WriteShapes()
{
	for (const auto& shape : m_shapes)
	{
		std::cout << shape->ToString() << std::endl;
	}
}

void ShapeController::PrintBiggestAreaShape()
{
	const auto it = std::ranges::max_element(m_shapes,
		[](const auto& shape1, const auto& shape2)
		{
			return shape1->GetArea() < shape2->GetArea();
		}
	);
	std::cout << (*it)->ToString() << std::endl;
}
// TODO: max_element min_element ++

void ShapeController::PrintShortestPerimeterShape()
{
	const auto it = std::ranges::max_element(m_shapes,
		[](const auto& shape1, const auto& shape2)
		{
			return shape1->GetPerimeter() > shape2->GetPerimeter();
		}
	);
	std::cout << (*it)->ToString() << std::endl;
}

void ShapeController::AddCircle()
{
	double x;
	double y;
	double radius;
	std::string outlineColor;
	std::string fillColor;

	m_input >> x >> y >> radius >> outlineColor >> fillColor;

	uint32_t outlineColorUint32 = StringToUint32(outlineColor);
	uint32_t fillColorUint32 = StringToUint32(fillColor);

	m_shapes.emplace_back(
		std::make_unique<Circle>(Point(x, y), radius, outlineColorUint32, fillColorUint32));
}

void ShapeController::AddLineSegment()
{
	double startX;
	double startY;
	double endX;
	double endY;
	std::string outlineColor;

	m_input >> startX >> startY >> endX >> endY >> outlineColor;

	uint32_t outlineColorUint32 = StringToUint32(outlineColor);

	m_shapes.emplace_back(std::make_unique<LineSegment>(
		Point(startX, startY), Point(endX, endY), outlineColorUint32));
}

void ShapeController::AddRectangle()
{
	double leftTopX;
	double leftTopY;
	double width;
	double height;
	std::string outlineColor;
	std::string fillColor;

	m_input >> leftTopX >> leftTopY >> width >> height >> outlineColor >> fillColor;

	const double rightBottomX = leftTopX + width;
	const double rightBottomY = leftTopY + height;

	uint32_t outlineColorUint32 = StringToUint32(outlineColor);
	uint32_t fillColorUint32 = StringToUint32(fillColor);

	m_shapes.emplace_back(std::make_unique<Rectangle>(Point(leftTopX, leftTopY),
		Point(rightBottomX, rightBottomY), outlineColorUint32, fillColorUint32));

	std::cout << leftTopX << " " << leftTopY << std::endl;
}

void ShapeController::AddTriangle()
{
	double vertex1X;
	double vertex1Y;
	double vertex2X;
	double vertex2Y;
	double vertex3X;
	double vertex3Y;
	std::string outlineColor;
	std::string fillColor;

	if (!(m_input >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y
			>> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid input");
	}

	uint32_t outlineColorUint32 = StringToUint32(outlineColor);
	uint32_t fillColorUint32 = StringToUint32(fillColor);

	m_shapes.emplace_back(std::make_unique<Triangle>(Point(vertex1X, vertex1X),
		Point(vertex2X, vertex2Y), Point(vertex3X, vertex3Y), outlineColorUint32, fillColorUint32));
}

uint32_t ShapeController::StringToUint32(const std::string& string)
{
	if (string.length() != 6)
	{
		throw std::invalid_argument("Invalid color string");
	}

	return std::stoul(string, nullptr, 16);
}
