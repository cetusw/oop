#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "SolidShape.h"
#include "../Point.h"

class Rectangle : public SolidShape
{
public:
    Rectangle(Point leftTop, Point rightBottom, uint32_t outlineColor, uint32_t fillColor);
    [[nodiscard]] Point GetLeftTop() const;
    [[nodiscard]] Point GetRightBottom() const;
    [[nodiscard]] double GetWidth() const;
    [[nodiscard]] double GetHeight() const;
	double GetArea() override;
	double GetPerimeter() override;

private:
	Point m_leftTop;
	Point m_rightBottom;
};


#endif //RECTANGLE_H
