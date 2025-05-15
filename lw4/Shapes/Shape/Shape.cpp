#include "Shape.h"

#include "SolidShape.h"

#include <iomanip>
#include <ios>

Shape::Shape(const uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

std::string Shape::ToString()
{
	std::string result = "Area: " + std::to_string(GetArea()) + "\n"
		+ "Perimetr: " + std::to_string(GetPerimeter()) + "\n"
		+ "OutlineColor: " + Uint32ToHexString(GetOutlineColor()) + "\n";

	if (const auto* solid = dynamic_cast<const ISolidShape*>(this))
	{
		result += "FillColor: " + Uint32ToHexString(solid->GetFillColor()) + "\n";
	}

	return result;
}

uint32_t Shape::GetOutlineColor() { return m_outlineColor; }

std::string Shape::Uint32ToHexString(const uint32_t value)
{
	std::ostringstream oss;
	oss << std::hex << std::uppercase << std::setw(6) << std::setfill('0') << value;
	return oss.str();
}