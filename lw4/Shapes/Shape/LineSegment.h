#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "../Point.h"
#include "Shape.h"

class LineSegment final : public Shape
{
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor);

	double GetArea() override;
	double GetPerimeter() override;

	[[nodiscard]] Point GetStartPoint() const;
	[[nodiscard]] Point GetEndPoint() const;
	void Draw(ICanvas& canvas) override;


private:
	Point m_startPoint{};
	Point m_endPoint{};

};

#endif // LINESEGMENT_H
