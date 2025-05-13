#ifndef SHAPE_H
#define SHAPE_H
#include "../Interface/IShape.h"

class Shape : public virtual IShape
{
public:
	explicit Shape(uint32_t outlineColor);
	std::string ToString() override;
	uint32_t GetOutlineColor() override;

private:
	uint32_t m_outlineColor;
};

#endif // SHAPE_H
