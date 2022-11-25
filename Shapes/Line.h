#pragma once

#include "Shape.h"

class Line : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Line(Point, Point, GfxInfo ShapeGfxInfo);
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
};