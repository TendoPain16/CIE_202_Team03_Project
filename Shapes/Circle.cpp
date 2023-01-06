#include "Circle.h"
#include <iostream>

Circle::Circle() {Center.x = 0; Center.y = 0; Radius.x = 0; Radius.y = 0;}


Circle::Circle(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	Center = P1;
	Radius = P2;
}



Circle::~Circle()
{}

void Circle::Draw(GUI* pUI) const
{
	//Call Output::DrawCIRC to draw a circle on the screen	
	pUI->DrawCircle(Center, Radius, ShpGfxInfo);
	if (resizing == true)
	{
		int rad = sqrt(pow(Center.x - Radius.x, 2) + pow(Center.y - Radius.y, 2));
		Point p1;
		p1.x = Center.x;
		p1.y = Center.y - rad;
		pUI->DrawSquareInPoint(p1);
		Point p2;
		p2.x = Center.x + rad;
		p2.y = Center.y;
		pUI->DrawSquareInPoint(p2);
		Point p3;
		p3.x = Center.x;
		p3.y = Center.y + rad;
		pUI->DrawSquareInPoint(p3);
		Point p4;
		p4.x = Center.x - rad;
		p4.y = Center.y;
		pUI->DrawSquareInPoint(p4);
	}
}

void Circle::Save(ofstream& file) const
{
	file << 2 << "\t"
		 << "Circle" << "\t"
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
		 << Center.x << "\t" << Center.y << "\t" 
		 << Radius.x << "\t" << Radius.y << endl;
}


void Circle::Load(vector <string> line, GUI* pUI, ifstream* inputfile)
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

	Center.x = stoi(line[11]); Center.y = stoi(line[12]);
	Radius.x = stoi(line[13]); Radius.y = stoi(line[14]);
}


void Circle::Resize(double number)
{
	int rad = sqrt(pow(Center.x - Radius.x, 2) + pow(Center.y - Radius.y, 2));
	rad = rad * number;

	Radius.x = Center.x + rad;
	Radius.y = Center.y;
}

int Circle::is_on_corners(Point x)
{
	int rad = sqrt(pow(Center.x - Radius.x, 2) + pow(Center.y - Radius.y, 2));
	int dist = sqrt(pow(Center.x - x.x, 2) + pow(Center.y - x.y, 2));
	if ((dist > rad - 10) && (dist < rad + 10))
	{
		return 1;
	}
	else
		return 0;
}

void Circle::Resize_By_Drag(int point_number, Point old_point, Point new_point)
{
	Radius.x = new_point.x;
	Radius.y = new_point.y;
}

void Circle::Move(Point old_point, Point new_point)
{
	int rad = sqrt(pow(Center.x - Radius.x, 2) + pow(Center.y - Radius.y, 2));
	int diff_x = new_point.x - old_point.x;
	int diff_y = new_point.y - old_point.y;

	Center.x = Center.x + diff_x;
	Center.y = Center.y + diff_y;
	Radius.x = Center.x + rad;
	Radius.y = Center.y;

}

bool Circle::IsPointInside(int x, int y)
{
	Point p;
	p.x = x;
	p.y = y;
	int rad = sqrt(pow(Center.x - Radius.x, 2) + pow(Center.y - Radius.y, 2));
	int dist = sqrt(pow(Center.x - p.x, 2) + pow(Center.y - p.y, 2));
	if (dist <= rad)
	{
		return true;
	}
	else
		return false;
}
