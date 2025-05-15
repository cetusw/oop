#include "Rectangle.h"

Rectangle::Rectangle(const Point leftTop, const Point rightBottom, const uint32_t outlineColor,
	const uint32_t fillColor)
	: SolidShape(outlineColor, fillColor)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

Point Rectangle::GetLeftTop() const { return m_leftTop; }

Point Rectangle::GetRightBottom() const { return m_rightBottom; }

double Rectangle::GetWidth() const { return m_rightBottom.x - m_leftTop.x; }

double Rectangle::GetHeight() const { return m_rightBottom.y - m_leftTop.y; }

double Rectangle::GetArea() { return GetWidth() * GetHeight(); }

double Rectangle::GetPerimeter() { return 2 * (GetWidth() + GetHeight()); }

uint32_t Rectangle::GetOutlineColor() { return SolidShape::GetOutlineColor(); }

uint32_t Rectangle::GetFillColor() const { return SolidShape::GetFillColor(); }

std::string Rectangle::ToString() { return SolidShape::ToString(); }