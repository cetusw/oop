#include "Circle.h"

#include <stdexcept>

Circle::Circle(
	const Point center, const double radius, const uint32_t outlineColor, const uint32_t fillColor)
	: SolidShape(outlineColor, fillColor)
	, m_center(center)
	, m_radius(radius)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Radius cannot be negative");
	}
}

double Circle::GetArea() { return std::numbers::pi * m_radius * m_radius; }

double Circle::GetPerimeter() { return 2 * std::numbers::pi * m_radius; }

Point Circle::GetCenter() const { return m_center; }

double Circle::GetRadius() const { return m_radius; }

// TODO: убрать реализацию ++
