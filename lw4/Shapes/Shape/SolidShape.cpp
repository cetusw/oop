#include "SolidShape.h"

#include "Shape.h"

SolidShape::SolidShape(const uint32_t outlineColor, const uint32_t fillColor)
	: Shape(outlineColor)
	, m_fillColor(fillColor)
{
}

uint32_t SolidShape::GetFillColor() const { return m_fillColor; }