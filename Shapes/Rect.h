#pragma once

#include "shape.h"

class Rect : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Rect();
	Rect(Point , Point, GfxInfo shapeGfxInfo );
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream&) const;
	virtual void Load(vector <string> line, GUI* pUI, ifstream* inputfile = nullptr);
	virtual void Resize(double number);
	virtual vector <shape*> get_shapes_list();
};

