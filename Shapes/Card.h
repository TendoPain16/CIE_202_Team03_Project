#pragma once
#include "shape.h" 
#include "..\GUI\GUI.h"
#include <fstream>
#include "Rect.h"

class Card
{
private:
	shape* pic;
	Point Card_Center;
	Point Corner1;
	Point Corner2;
	GfxInfo Card_Info;
public:
	Card();
	Card(shape* photo, Point Center);
	virtual ~Card();

	double calc_area_of_triangle(Point p1, Point p2, Point p3);
	bool is_covered();
	void set_covered(bool x);
	virtual bool IsPointInside(int x, int y);
	void Draw(GUI* pUI);
	bool check_card(Card* temp);

};
