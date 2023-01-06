#pragma once

#include "shape.h"

class Square : public shape
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
	Point Corner4;
public:
	Square();
	Square(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Square();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream&) const;
	virtual void Load(vector <string> line, GUI* pUI, ifstream* inputfile = nullptr);
	virtual void Resize(double number);
	virtual void Move(Point old_point, Point new_point);
	virtual int is_on_corners(Point x);
	virtual void Resize_By_Drag(int point_number, Point old_point, Point new_point);
	virtual bool IsPointInside(int x, int y);
};

