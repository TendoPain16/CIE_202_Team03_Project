#pragma once

#include "shape.h"
#include <fstream>

class Circle : public shape
{
private:
	Point Center;
	Point Radius;
public:
	Circle();
	Circle(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream& info) const;
	virtual void Load(vector <string> line, GUI* pUI);
};
