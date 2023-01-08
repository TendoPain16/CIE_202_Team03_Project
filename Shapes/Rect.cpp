#include "Rect.h"
#include <iostream>

Rect::Rect() {Corner1.x = 0; Corner1.y = 0; Corner2.x = 0; Corner2.y = 0;}


Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	ID = Get_ID();
	Corner1 = P1;
	Corner2 = P2;
}

Rect::Rect(Rect* x)
{
	this->Corner1 = x->Corner1;
	this->Corner2 = x->Corner2;
	this->resizing = x->resizing;
	this->ShpGfxInfo = x->ShpGfxInfo;
	this->ID = x->ID;
}

Rect::~Rect()
{}

void Rect::Draw(GUI* pUI) const
{
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);	//Call Output::DrawRect to draw a rectangle on the screen
	if (resizing == true)
	{
		Point Corner3;
		Point Corner4;
		Corner3.x = Corner1.x;
		Corner3.y = Corner2.y;
		Corner4.x = Corner2.x;
		Corner4.y = Corner1.y;
		pUI->DrawSquareInPoint(Corner1);
		pUI->DrawSquareInPoint(Corner2);
		pUI->DrawSquareInPoint(Corner3);
		pUI->DrawSquareInPoint(Corner4);
	}
}


void Rect::Save(ofstream& file) const
{
	file << 0 << "\t" 
		 << "Rectangle" << "\t"
		 << ID << "\t"
		 << int(ShpGfxInfo.DrawClr.ucRed) << "\t"
		 << int(ShpGfxInfo.DrawClr.ucGreen) << "\t"
		 << int(ShpGfxInfo.DrawClr.ucBlue) << "\t";

	if (ShpGfxInfo.isFilled)
		file << int(ShpGfxInfo.FillClr.ucRed) << "\t" 
			 << int(ShpGfxInfo.FillClr.ucGreen) << "\t"
			 << int(ShpGfxInfo.FillClr.ucBlue) << "\t";
	else
		file << "NotFilled" << "\t" 
			 << "NotFilled" << "\t"
			 << "NotFilled" << "\t";

	file << ShpGfxInfo.BorderWdth << "\t" 
		 << ShpGfxInfo.image << "\t" 
		 << Corner1.x << "\t" << Corner1.y << "\t" 
		 << Corner2.x << "\t" << Corner2.y << endl;
}


void Rect::Load(vector <string> line,GUI* pUI, ifstream* inputfile)
{
	ID = stoi(line[2]);
	if (ID >= ID_gen)
		ID_gen = ID;
	ShpGfxInfo.DrawClr = color(stoi(line[3]), stoi(line[4]), stoi(line[5]));
	ShpGfxInfo.isSelected = false;

	ShpGfxInfo.isFilled = false;
	if (line[6] != "NotFilled")
	{
		ShpGfxInfo.isFilled = true;
		ShpGfxInfo.FillClr = color(stoi(line[6]), stoi(line[7]), stoi(line[8]));
	}

	ShpGfxInfo.BorderWdth = stoi(line[9]);
	ShpGfxInfo.image = line[10];

	Corner1.x = stoi(line[11]); Corner1.y = stoi(line[12]);
	Corner2.x = stoi(line[13]); Corner2.y = stoi(line[14]);
}


void Rect::Resize(double number)
{
	Point mid;
	mid.x = (Corner1.x + Corner2.x) / 2;
	mid.y = (Corner1.y + Corner2.y) / 2;
	scale_two_points(mid, Corner1, number);
	scale_two_points(mid, Corner2, number);
}

int Rect::is_on_corners(Point x)
{
	Point p1;
	Point p2;
	Point Corner3;
	Point Corner4;
	Corner3.x = Corner1.x;
	Corner3.y = Corner2.y;
	Corner4.x = Corner2.x;
	Corner4.y = Corner1.y;
	vector <Point> list;
	list.push_back(Corner1);	list.push_back(Corner2);	list.push_back(Corner3);	list.push_back(Corner4);
	for (int i = 0; i < 4; i++)
	{
		p1.x = list[i].x - 5;
		p1.y = list[i].y - 5;
		p2.x = list[i].x + 5;
		p2.y = list[i].y + 5;
		if (((p1.x >= x.x) && (x.x >= p2.x) && (p1.y >= x.y) && (x.y >= p2.y)) || ((p1.x <= x.x) && (x.x <= p2.x) && (p1.y <= x.y) && (x.y <= p2.y)))
		{
			return i + 1;
		}
	}
	return 0;
}


void Rect::Resize_By_Drag(int point_number, Point old_point, Point new_point)
{
	switch (point_number)
	{
	case 1: Corner1 = new_point; break;
	case 2: Corner2 = new_point; break;
	case 3: Corner1.x = new_point.x; Corner2.y = new_point.y; break;
	case 4: Corner2.x = new_point.x; Corner1.y = new_point.y; break;
	}
}

void Rect::Move(Point old_point, Point new_point)
{
	int diff_x = new_point.x - old_point.x;
	int diff_y = new_point.y - old_point.y;

	Corner1.x = Corner1.x + diff_x;
	Corner1.y = Corner1.y + diff_y;
	Corner2.x = Corner2.x + diff_x;
	Corner2.y = Corner2.y + diff_y;
}

bool Rect::IsPointInside(int x, int y)
{
	Point temp;
	temp.x = x;
	temp.y = y;

	Point Corner3;
	Corner3.x = Corner2.x;
	Corner3.y = Corner1.y;

	Point Corner4;
	Corner4.x = Corner1.x;
	Corner4.y = Corner2.y;

	double tri_1 = calc_area_of_triangle(Corner1,Corner3,temp);
	double tri_2 = calc_area_of_triangle(Corner3, Corner2, temp);
	double tri_3 = calc_area_of_triangle(Corner2, Corner4, temp);
	double tri_4 = calc_area_of_triangle(Corner4, Corner1, temp);
	double area_of_rect = abs(Corner1.x - Corner2.x) * abs(Corner1.y - Corner2.y);

	if (area_of_rect == tri_1 + tri_2 + tri_3 + tri_4)
	{
		return true;
	}
	else
		return false;
}

void Rect::save_shape_points()
{
	shape_points.push_back(Corner1);
	shape_points.push_back(Corner2);
}
void Rect::load_shape_points()
{
	Corner1 = shape_points[0];
	Corner2 = shape_points[1];
}
bool Rect::is_shape_between_two_corners(Point p1, Point p2)
{
	bool x = is_point_inside_rect(p1,p2,Corner1);
	bool y = is_point_inside_rect(p1, p2, Corner2);
	if (x && y)
	{
		return true;
	}
	else
		return false;
}

void Rect::move_to_center(Point new_center)
{
	Point Center;
	Center.x = (Corner1.x + Corner2.x) / 2;
	Center.y = (Corner1.y + Corner2.y) / 2;

	int diff_x = new_center.x - Center.x;
	int diff_y = new_center.y - Center.y;

	Corner1.x = Corner1.x + diff_x;
	Corner1.y = Corner1.y + diff_y;
	Corner2.x = Corner2.x + diff_x;
	Corner2.y = Corner2.y + diff_y;
}