#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "../Shape/Shape.h"

#include <vector>

class ShapeController
{
public:
	explicit ShapeController(std::istream& input);

	void ReadShapes();

	void AddCircle();

	void AddLineSegment();

	void AddRectangle();

	void AddTriangle();

private:
	static static uint32_t StringToUint32(const std::string& string);

	std::vector<std::unique_ptr<Shape>> m_shapes;
	std::istream& m_input;
	std::pmr::unordered_map<std::string, std::function<void()>> m_commands;
};

#endif // SHAPECONTROLLER_H
