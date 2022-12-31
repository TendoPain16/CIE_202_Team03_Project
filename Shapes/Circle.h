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
	virtual void Save(ofstream&) const;
	virtual void Load(vector <string> line, GUI* pUI, ifstream* inputfile = nullptr) override;
	virtual void Resize(double number);
	virtual vector <shape*> get_shapes_list();
};
