#ifndef ISHAPE_H
#define ISHAPE_H

#pragma once

#include "ICanvasDrawable.h"

#include <cstdint>
#include <string>

class IShape : public ICanvasDrawable
{
public:
	virtual std::string ToString() = 0;
	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual uint32_t GetOutlineColor() = 0;
};

#endif // ISHAPE_H
