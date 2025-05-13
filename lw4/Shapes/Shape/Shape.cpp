#include "Shape.h"

#include "SolidShape.h"

Shape::Shape(const uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

std::string Shape::ToString()
{
	return "Area: " + std::to_string(GetArea()) + "\n"
		+ "Perimetr: " + std::to_string(GetPerimeter()) + "\n"
		+ "OutlineColor: " + std::to_string(GetOutlineColor()) + "\n";
}

uint32_t Shape::GetOutlineColor()
{
	return m_outlineColor;
}