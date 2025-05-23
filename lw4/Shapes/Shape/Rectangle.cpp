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

double Rectangle::GetWidth() const { return std::abs(m_rightBottom.y - m_leftTop.y); }

double Rectangle::GetHeight() const { return std::abs(m_rightBottom.x - m_leftTop.x); }

void Rectangle::Draw(ICanvas& canvas)
{
	canvas.DrawRectangle(m_leftTop, GetWidth(), GetHeight(), SolidShape::GetOutlineColor(), SolidShape::GetFillColor());
}

double Rectangle::GetArea() { return GetWidth() * GetHeight(); }

double Rectangle::GetPerimeter() { return 2 * (GetWidth() + GetHeight()); }

// TODO: убрать реализацию ++