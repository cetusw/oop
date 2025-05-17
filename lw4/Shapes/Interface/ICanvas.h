#ifndef ICANVAS_H
#define ICANVAS_H
#include "../Point.h"
#include <vector>
#include <cstdint>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(Point from, Point to, uint32_t outlineColor) = 0;
	virtual void DrawPolygon(const std::vector<Point>& points, uint32_t outlineColor, uint32_t fillColor) = 0;
	virtual void DrawRectangle(Point position, double width, double height, uint32_t outlineColor, uint32_t fillColor) = 0;
	virtual void DrawCircle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor) = 0;
};

#endif //ICANVAS_H
