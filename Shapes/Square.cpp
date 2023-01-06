#include "Square.h"
#include <iostream>

Square::Square() {Corner1.x = 0; Corner1.y = 0; Corner2.x = 0; Corner2.y = 0; Corner3.x = 0; Corner3.y = 0; Corner4.x = 0; Corner4.y = 0;}


Square::Square(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	Corner1 = P1;
	Corner2 = P2;

	Corner3.x = P2.x;
	Corner3.y = P1.y;
	Corner4.x = P1.x;
	Corner4.y = P2.y;
}



Square::~Square()
{}

void Square::Draw(GUI* pUI) const
{
	pUI->DrawSquare(Corner1, Corner2, ShpGfxInfo);	 //Call Output::DrawSQUA to draw a square on the screen	
	if (resizing == true)
	{
		pUI->DrawSquareInPoint(Corner1);
		pUI->DrawSquareInPoint(Corner2);
		pUI->DrawSquareInPoint(Corner3);
		pUI->DrawSquareInPoint(Corner4);
	}
}


void Square::Save(ofstream& file) const
{
	file << 1 << "\t" 
		 << "Square" << "\t" 
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

void Square::Load(vector <string> line, GUI* pUI, ifstream* inputfile)
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


void Square::Resize(double number)
{
	Point mid;
	mid.x = (Corner1.x + Corner2.x) / 2;
	mid.y = (Corner1.y + Corner2.y) / 2;
	scale_two_points(mid, Corner1, number);
	scale_two_points(mid, Corner2, number);
	scale_two_points(mid, Corner3, number);
	scale_two_points(mid, Corner4, number);
}


int Square::is_on_corners(Point x)
{
	Point p1;
	Point p2;
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


void Square::Resize_By_Drag(int point_number, Point old_point, Point new_point)
{
	Point f_new_point;
	switch (point_number)
	{
	case 1:
		f_new_point.x = Corner2.x - (Corner2.x - new_point.x);
		f_new_point.y = Corner2.y - (Corner2.x - new_point.x);
		Corner1 = f_new_point;
		Corner3.x = Corner2.x;
		Corner3.y = Corner1.y;
		Corner4.x = Corner1.x;
		Corner4.y = Corner2.y;
		break;
	case 2:
		f_new_point.x = Corner1.x + (new_point.x - Corner1.x);
		f_new_point.y = Corner1.y + (new_point.x - Corner1.x);
		Corner2 = f_new_point;
		Corner3.x = Corner2.x;
		Corner3.y = Corner1.y;
		Corner4.x = Corner1.x;
		Corner4.y = Corner2.y;
		break;
	case 3:
		f_new_point.x = Corner4.x + (new_point.x - Corner4.x);
		f_new_point.y = Corner4.y - (new_point.x - Corner4.x);
		Corner3 = f_new_point;
		Corner1.y = Corner4.y - (new_point.x - Corner4.x);
		Corner2.x = Corner4.x + (new_point.x - Corner4.x);
		break;
	case 4:
		f_new_point.x = Corner3.x - (Corner3.x - new_point.x);
		f_new_point.y = Corner3.y + (Corner3.x - new_point.x);
		Corner4 = f_new_point;
		Corner1.x = Corner3.x - (Corner3.x - new_point.x);
		Corner2.y = Corner3.y + (Corner3.x - new_point.x);
		break;
	}
}



void Square::Move(Point old_point, Point new_point)
{
	int diff_x = new_point.x - old_point.x;
	int diff_y = new_point.y - old_point.y;

	Corner1.x = Corner1.x + diff_x;
	Corner1.y = Corner1.y + diff_y;
	Corner2.x = Corner2.x + diff_x;
	Corner2.y = Corner2.y + diff_y;
	Corner3.x = Corner3.x + diff_x;
	Corner3.y = Corner3.y + diff_y;
	Corner4.x = Corner4.x + diff_x;
	Corner4.y = Corner4.y + diff_y;
}

bool Square::IsPointInside(int x, int y)
{
	Point temp;
	temp.x = x;
	temp.y = y;

	double tri_1 = calc_area_of_triangle(Corner1, Corner3, temp);
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

