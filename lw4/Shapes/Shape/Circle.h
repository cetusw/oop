#ifndef CIRCLE_H
#define CIRCLE_H
#include "../Point.h"
#include "SolidShape.h"

class Circle final : public SolidShape
{
public:
	Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	uint32_t GetOutlineColor() override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	std::string ToString() override;

	[[nodiscard]] Point GetCenter() const;
	[[nodiscard]] double GetRadius() const;

private:
	Point m_center;
	double m_radius;
};

#endif // CIRCLE_H
