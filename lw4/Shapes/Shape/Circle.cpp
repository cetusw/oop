#include "Circle.h"

Circle::Circle(
	const Point center, const double radius, const uint32_t outlineColor, const uint32_t fillColor)
	: SolidShape(outlineColor, fillColor)
	, m_center(center)
	, m_radius(radius)
{
}

// TODO: добавить валидацию в конструкторах фигур

double Circle::GetArea() { return std::numbers::pi * m_radius * m_radius; }

double Circle::GetPerimeter() { return 2 * std::numbers::pi * m_radius; }

uint32_t Circle::GetOutlineColor() { return SolidShape::GetOutlineColor(); }

uint32_t Circle::GetFillColor() const { return SolidShape::GetFillColor(); }

std::string Circle::ToString() { return SolidShape::ToString(); }

Point Circle::GetCenter() const { return m_center; }

double Circle::GetRadius() const { return m_radius; }
