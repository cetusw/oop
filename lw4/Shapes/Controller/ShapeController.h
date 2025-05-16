#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#include <functional>
#include <memory>
#include <unordered_map>

#include "../Shape/Shape.h"

#include <vector>

class ShapeController
{
public:
	explicit ShapeController(std::istream& input);

	void ReadShapes();

	void WriteShapes();

    std::string PrintBiggestAreaShape();

	std::string PrintShortestPerimeterShape();

	void AddCircle();

	void AddLineSegment();

	void AddRectangle();

	void AddTriangle();

private:
	static uint32_t StringToUint32(const std::string& string);

	std::vector<std::unique_ptr<Shape>> m_shapes;
	std::istream& m_input;
	std::unordered_map<std::string, std::function<void()>> m_commands;
};

#endif // SHAPECONTROLLER_H
