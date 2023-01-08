#include "Line.h"
#include <iostream>

Line::Line() {Corner1.x = 0; Corner1.y = 0; Corner2.x = 0; Corner2.y = 0;}


Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	Corner1 = P1;
	Corner2 = P2;
}

Line::Line(Line* x)
{
	this->Corner1 = x->Corner1;
	this->Corner2 = x->Corner2;
	this->resizing = x->resizing;
	this->ShpGfxInfo = x->ShpGfxInfo;
	this->ID = x->ID;
}

Line::~Line()
{}

void Line::Draw(GUI* pUI) const
{
	pUI->DrawLine(Corner1, Corner2, ShpGfxInfo);	//Call Output::Drawline to draw a line on the screen	
	if (resizing == true)
	{
		pUI->DrawSquareInPoint(Corner1);
		pUI->DrawSquareInPoint(Corner2);
	}
}


void Line::Save(ofstream& file) const
{
	file << 3 << "\t" 
		 << "Line" << "\t" 
		 << ID << "\t" 
		 << int(ShpGfxInfo.DrawClr.ucRed) << "\t" 
		 << int(ShpGfxInfo.DrawClr.ucGreen) << "\t" 
		 << int(ShpGfxInfo.DrawClr.ucBlue) << "\t";

	file  << ShpGfxInfo.BorderWdth << "\t"
		  << ShpGfxInfo.image << "\t" 
		  << Corner1.x << "\t" << Corner1.y << "\t" 
		  << Corner2.x << "\t" << Corner2.y << endl;
}


void Line::Load(vector <string> line, GUI* pUI, ifstream* inputfile)
{
	ID = stoi(line[2]);
	if (ID >= ID_gen)
		ID_gen = ID;
	ShpGfxInfo.DrawClr = color(stoi(line[3]), stoi(line[4]), stoi(line[5]));
	ShpGfxInfo.isSelected = false;
	ShpGfxInfo.isFilled = false;

	ShpGfxInfo.BorderWdth = stoi(line[6]);
	ShpGfxInfo.image = line[7];

	Corner1.x = stoi(line[8]); Corner1.y = stoi(line[9]);
	Corner2.x = stoi(line[10]); Corner2.y = stoi(line[11]);
}


void Line::Resize(double number)
{
	Point mid;
	mid.x = (Corner1.x + Corner2.x) / 2;
	mid.y = (Corner1.y + Corner2.y) / 2;
	scale_two_points(mid, Corner1, number);
	scale_two_points(mid, Corner2, number);
}

int Line::is_on_corners(Point x)
{
	Point p1;
	Point p2;
	vector <Point> list;
	list.push_back(Corner1);	list.push_back(Corner2);
	for (int i = 0; i < 2; i++)
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


void Line::Resize_By_Drag(int point_number, Point old_point, Point new_point)
{
	switch (point_number)
	{
	case 1: Corner1 = new_point; break;
	case 2: Corner2 = new_point; break;
	}
}

void Line::Move(Point old_point, Point new_point)
{
	int diff_x = new_point.x - old_point.x;
	int diff_y = new_point.y - old_point.y;
	Point Center;
	Corner1.x = Corner1.x + diff_x;
	Corner1.y = Corner1.y + diff_y;
	Corner2.x = Corner2.x + diff_x;
	Corner2.y = Corner2.y + diff_y;
}

bool Line::IsPointInside(int x, int y)
{
Point P; P.x = x; P.y = y;
Point P1 = Corner1;
Point P2 = Corner2;

double area = calc_area_of_triangle(P1, P2, P);
int distance = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
double dist_to_line = area / (distance * 0.5);

if ((P.x >= P1.x && P.y >= P1.y && P.x <= P2.x && P.y <= P2.y) || (P.x >= P2.x && P.y >= P2.y && P.x <= P1.x && P.y <= P1.y))
{
	if (dist_to_line <= 20)
	{
		return true;
	}
	else
		return false;
}
else 
	return false;
}


void Line::save_shape_points()
{
	shape_points.push_back(Corner1);
	shape_points.push_back(Corner2);
}
void Line::load_shape_points()
{
	Corner1 = shape_points[0];
	Corner2 = shape_points[1];
}
bool Line::is_shape_between_two_corners(Point p1, Point p2)
{
	bool x = is_point_inside_rect(p1, p2, Corner1);
	bool y = is_point_inside_rect(p1, p2, Corner2);
	if (x && y)
	{
		return true;
	}
	else
		return false;
}

void Line::move_to_center(Point new_center)
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