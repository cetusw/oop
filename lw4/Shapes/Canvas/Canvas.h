#ifndef CANVAS_H
#define CANVAS_H
#include "../Interface/ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas final : public ICanvas
{
public:
	explicit Canvas(sf::RenderWindow& window);
	void DrawLine(Point from, Point to, uint32_t outlineColor) override;
	void DrawPolygon(const std::vector<Point>& points, uint32_t outlineColor, uint32_t fillColor) override;
	void DrawRectangle(Point position, double width, double height, uint32_t outlineColor, uint32_t fillColor) override;
	void DrawCircle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor) override;

private:
	static sf::Color UintToColor(uint32_t color);
	sf::RenderWindow& m_window;

};

#endif // CANVAS_H
