#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "../Point.h"
#include "Shape.h"

class LineSegment : public Shape
{
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor);
	[[nodiscard]] Point GetStartPoint() const;
	[[nodiscard]] Point GetEndPoint() const;
	[[nodiscard]] double GetLength() const;

private:
	Point m_startPoint{};
	Point m_endPoint{};

};

#endif // LINESEGMENT_H
