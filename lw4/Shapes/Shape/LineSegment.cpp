#include "LineSegment.h"
#include <cmath>

LineSegment::LineSegment(const Point startPoint, const Point endPoint, const uint32_t outlineColor)
	: Shape(outlineColor)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

Point LineSegment::GetStartPoint() const { return m_startPoint; }

Point LineSegment::GetEndPoint() const { return m_endPoint; }

double LineSegment::GetLength() const
{
	return std::hypot((m_endPoint.x - m_startPoint.x), (m_endPoint.y - m_startPoint.y));
}
