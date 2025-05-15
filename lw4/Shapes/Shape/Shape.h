#ifndef SHAPE_H
#define SHAPE_H
#include "../Interface/IShape.h"

class Shape : virtual public IShape
{
public:
	explicit Shape(uint32_t outlineColor);

	std::string ToString() override;
	uint32_t GetOutlineColor() override;

private:
	static std::string Uint32ToHexString(uint32_t value);
	uint32_t m_outlineColor;
};

#endif // SHAPE_H
