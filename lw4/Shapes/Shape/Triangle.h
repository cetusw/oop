#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "SolidShape.h"
#include "../Point.h"

class Triangle : public SolidShape
{
public:
    Triangle(Point vertex1, Point vertex2, Point vertex3, uint32_t outlineColor, uint32_t fillColor);
    [[nodiscard]] Point GetVertex1() const;
    [[nodiscard]] Point GetVertex2() const;
    [[nodiscard]] Point GetVertex3() const;
	double GetArea() override;
	double GetPerimeter() override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};


#endif //TRIANGLE_H
