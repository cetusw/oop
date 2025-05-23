#include "LineSegment.h"
#include <cmath>

LineSegment::LineSegment(const Point startPoint, const Point endPoint, const uint32_t outlineColor)
	: Shape(outlineColor)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

double LineSegment::GetArea() { return GetPerimeter(); }

double LineSegment::GetPerimeter()
{
	return std::hypot((m_endPoint.x - m_startPoint.x), (m_endPoint.y - m_startPoint.y));
}

Point LineSegment::GetStartPoint() const { return m_startPoint; }

Point LineSegment::GetEndPoint() const { return m_endPoint; }

void LineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_startPoint, m_endPoint, Shape::GetOutlineColor());
}
