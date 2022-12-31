#pragma once

#include "shape.h"

class IrregularPolygon : public shape
{
private:
	int V_number;
	vector <Point> Points;
public:
	IrregularPolygon();
	IrregularPolygon(vector <Point> Points,int V_number, GfxInfo shapeGfxInfo);
	virtual ~IrregularPolygon();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream&) const;
	virtual void Load(vector <string> line, GUI* pUI, ifstream* inputfile = nullptr);
	virtual void Resize(double number);
	virtual vector <shape*> get_shapes_list();
};
