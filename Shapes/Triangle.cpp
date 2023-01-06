#include "Triangle.h"
#include <iostream>

Triangle::Triangle(){Corner1.x = 0; Corner1.y = 0; Corner2.x = 0; Corner2.y = 0; Corner3.x = 0; Corner3.y = 0;}


Triangle::Triangle(Point P1, Point P2,Point P3, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}


Triangle::~Triangle()
{}

void Triangle::Draw(GUI* pUI) const
{
	pUI->DrawTriangle(Corner1, Corner2, Corner3, ShpGfxInfo);	//Call Output::DrawTrinagle to draw a rectangle on the screen	
	if (resizing  == true)
	{
		pUI->DrawSquareInPoint(Corner1);
		pUI->DrawSquareInPoint(Corner2);
		pUI->DrawSquareInPoint(Corner3);
	}
}


void Triangle::Save(ofstream& file) const
{
	file << 4 << "\t" 
		 << "Triangle" << "\t"
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
		 << Corner2.x << "\t" << Corner2.y << "\t" 
		 << Corner3.x << "\t" << Corner3.y << endl;
}


void Triangle::Load(vector <string> line, GUI* pUI, ifstream* inputfile)
{
	ID = stoi(line[2]);
	if (ID >= ID_gen)
		ID_gen = ID;
	ShpGfxInfo.isSelected = false;
	ShpGfxInfo.DrawClr = color(stoi(line[3]), stoi(line[4]), stoi(line[5]));

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
	Corner3.x = stoi(line[15]); Corner3.y = stoi(line[16]);
}

void Triangle::Resize(double number)
{
	Point mid;
	mid.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	mid.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	scale_two_points(mid, Corner1, number);
	scale_two_points(mid, Corner2, number);
	scale_two_points(mid, Corner3, number);
}

int Triangle::is_on_corners(Point x)
{
	Point p1;
	Point p2;
	vector <Point> list;
	list.push_back(Corner1);	list.push_back(Corner2);	list.push_back(Corner3);
	for (int i = 0; i < 3; i++)
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


void Triangle::Resize_By_Drag(int point_number, Point old_point, Point new_point)
{
	switch (point_number)
	{
	case 1: Corner1 = new_point; break;
	case 2: Corner2 = new_point; break;
	case 3: Corner3 = new_point; break;
	}
}

void Triangle::Move(Point old_point, Point new_point)
{
	int diff_x = new_point.x - old_point.x;
	int diff_y = new_point.y - old_point.y;

	Corner1.x = Corner1.x + diff_x;
	Corner1.y = Corner1.y + diff_y;
	Corner2.x = Corner2.x + diff_x;
	Corner2.y = Corner2.y + diff_y;
	Corner3.x = Corner3.x + diff_x;
	Corner3.y = Corner3.y + diff_y;
}

bool Triangle::IsPointInside(int x, int y)
{
	Point temp;
	temp.x = x;
	temp.y = y;

	double tri_1 = calc_area_of_triangle(Corner1, Corner2, temp);
	double tri_2 = calc_area_of_triangle(Corner2, Corner3, temp);
	double tri_3 = calc_area_of_triangle(Corner3, Corner1, temp);

	double area_of_triangle = calc_area_of_triangle(Corner1, Corner2, Corner3);

	if (area_of_triangle == tri_1 + tri_2 + tri_3)
	{
		return true;
	}
	else
		return false;
}