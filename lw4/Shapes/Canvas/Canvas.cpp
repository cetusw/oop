#include "Canvas.h"

constexpr int OUTLINE_THICKNESS = 1;

Canvas::Canvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void Canvas::DrawLine(const Point from, const Point to, const uint32_t outlineColor)
{
	sf::Vertex line[]
		= { sf::Vertex(sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y))),
			  sf::Vertex(sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y))) };
	line[0].color = UintToColor(outlineColor);
	line[1].color = UintToColor(outlineColor);
	m_window.draw(line, 2, sf::Lines);
}

void Canvas::DrawPolygon(
	const std::vector<Point>& points, const uint32_t outlineColor, const uint32_t fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(
			i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}
	polygon.setFillColor(UintToColor(fillColor));
	polygon.setOutlineColor(UintToColor(outlineColor));
	polygon.setOutlineThickness(1);
	m_window.draw(polygon);
}

void Canvas::DrawRectangle(const Point position, const double width, const double height,
	const uint32_t outlineColor, const uint32_t fillColor)
{
	sf::RectangleShape rect(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	rect.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
	rect.setFillColor(UintToColor(fillColor));
	rect.setOutlineColor(UintToColor(outlineColor));
	rect.setOutlineThickness(OUTLINE_THICKNESS);
	m_window.draw(rect);
}

void Canvas::DrawCircle(
	const Point center, const double radius, const uint32_t outlineColor, const uint32_t fillColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(
		static_cast<float>(center.x - radius), static_cast<float>(center.y - radius));
	circle.setFillColor(UintToColor(fillColor));
	circle.setOutlineColor(UintToColor(outlineColor));
	circle.setOutlineThickness(OUTLINE_THICKNESS);
	m_window.draw(circle);
}

sf::Color Canvas::UintToColor(const uint32_t color)
{
	return { static_cast<sf::Uint8>((color >> 16) & 0xFF),
		static_cast<sf::Uint8>((color >> 8) & 0xFF), static_cast<sf::Uint8>(color & 0xFF), 255 };
}
