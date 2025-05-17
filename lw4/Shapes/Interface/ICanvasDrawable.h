#ifndef ICANVASDRAWABLE_H
#define ICANVASDRAWABLE_H
#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual ~ICanvasDrawable() = default;
	virtual void Draw(ICanvas& canvas) = 0;
};

#endif //ICANVASDRAWABLE_H
