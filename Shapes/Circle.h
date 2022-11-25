#pragma once

#include "shape.h"

class Circle : public shape
{
private:
	Point Center;
	Point Radius;
public:
	Circle(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
};
