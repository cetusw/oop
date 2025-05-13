#include "Triangle.h"

#include "LineSegment.h"

Triangle::Triangle(const Point vertex1, const Point vertex2, const Point vertex3,
	const uint32_t outlineColor, const uint32_t fillColor)
	: SolidShape(outlineColor, fillColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

Point Triangle::GetVertex1() const { return m_vertex1; }

Point Triangle::GetVertex2() const { return m_vertex2; }

Point Triangle::GetVertex3() const { return m_vertex3; }
double Triangle::GetArea()
{
	return 0.5
		* ((m_vertex1.x - m_vertex3.x) * (m_vertex2.y - m_vertex3.y)
			- (m_vertex2.x - m_vertex3.x) * (m_vertex2.y - m_vertex3.y));
}
double Triangle::GetPerimeter()
{
	auto line = LineSegment(m_vertex1, m_vertex2, 0x000000);
	return
}