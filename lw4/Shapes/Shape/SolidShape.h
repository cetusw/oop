#ifndef SOLIDSHAPE_H
#define SOLIDSHAPE_H
#include "../Interface/ISolidShape.h"
#include "Shape.h"

class SolidShape : public ISolidShape, public Shape
{
public:
	explicit SolidShape(uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]] uint32_t GetFillColor() const override;

private:
	uint32_t m_fillColor;
};

#endif // SOLIDSHAPE_H

// TODO: разобраться с virtual ++ (проблема ромба, посмотреть на диаграмму, создание двух копий)
