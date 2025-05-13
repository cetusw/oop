#ifndef CIRCLE_H
#define CIRCLE_H
#include "../Point.h"
#include "SolidShape.h"

class Circle : public SolidShape
{
public:
	Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	[[nodiscard]] Point GetCenter() const;
	[[nodiscard]] double GetRadius() const;

private:
	Point m_center;
	double m_radius;
};

#endif // CIRCLE_H
