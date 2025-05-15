#ifndef ISOLIDSHAPE_H
#define ISOLIDSHAPE_H
#include "IShape.h"

class ISolidShape : virtual public IShape
{
public:
	[[nodiscard]] virtual uint32_t GetFillColor() const = 0;

};

#endif // ISOLIDSHAPE_H
