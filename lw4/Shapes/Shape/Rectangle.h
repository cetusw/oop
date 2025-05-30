#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "SolidShape.h"
#include "../Point.h"

class Rectangle final : public SolidShape
{
public:
    Rectangle(Point leftTop, Point rightBottom, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;

    [[nodiscard]] Point GetLeftTop() const;
    [[nodiscard]] Point GetRightBottom() const;
    [[nodiscard]] double GetWidth() const;
    [[nodiscard]] double GetHeight() const;
	void Draw(ICanvas& canvas) override;

private:
	Point m_leftTop;
	Point m_rightBottom;
};


#endif //RECTANGLE_H
