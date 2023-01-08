#include "IrregularPolygon.h"
#include <iostream>

IrregularPolygon::IrregularPolygon() {V_number = 0;}


IrregularPolygon::IrregularPolygon(vector <Point> Points, int V_number, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	this->Points = Points;
	this->V_number = V_number;
	ShpGfxInfo = shapeGfxInfo;
}

IrregularPolygon::IrregularPolygon(IrregularPolygon* x)
{
	for (int i = 0; i < (x->Points).size(); i++)
	{
		this->Points.push_back((x->Points)[i]);
	}
	this->V_number = x->V_number;
	this->resizing = x->resizing;
	this->ShpGfxInfo = x->ShpGfxInfo;
	this->ID = x->ID;
}

IrregularPolygon::~IrregularPolygon()
{}

void IrregularPolygon::Draw(GUI* pUI) const
{
	pUI->DrawIrregularpolygon(Points, V_number, ShpGfxInfo);	//Call Output::DrawIrregularPolygon to draw a IrregulatPolygon on the screen
	if (resizing == true)
	{
		for (int i = 0; i < Points.size(); i++)
		{
			pUI->DrawSquareInPoint(Points[i]);
		}
	}
}


void IrregularPolygon::Save(ofstream& file) const
{
	file << 5 << "\t"
		 << "IrregularPolygon" << "\t" 
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
		 << V_number;

	for (int i = 0; i < V_number; i++)
	{
		file <<"\t" << Points[i].x << "\t" << Points[i].y;
	}
	file << endl;
}


void IrregularPolygon::Load(vector <string> line, GUI* pUI, ifstream* inputfile)
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
	V_number = stoi(line[11]);


	Point tmp;
	int j = 0;
	for (int i = 0; i < V_number; i++)
	{
		tmp.x = stoi(line[12+j]);
		tmp.y = stoi(line[13+j]);
		Points.push_back(tmp);
		j = j + 2;
	}
	j = 0;
}


void IrregularPolygon::Resize(double number)
{
	int x_sum = 0;
	int y_sum = 0;
	for (auto temp : Points)
	{
		x_sum = x_sum + temp.x;
		y_sum = y_sum + temp.y;
	}

	Point mid;
	mid.x = x_sum / Points.size();
	mid.y = y_sum / Points.size();
	for (int i = 0; i < Points.size(); i++)
	{
		scale_two_points(mid, Points[i], number);
	}	
}

int IrregularPolygon::is_on_corners(Point x)
{
	Point p1;
	Point p2;
	for (int i = 0; i < Points.size(); i++)
	{
		p1.x = Points[i].x - 5;
		p1.y = Points[i].y - 5;
		p2.x = Points[i].x + 5;
		p2.y = Points[i].y + 5;
		if (((p1.x >= x.x) && (x.x >= p2.x) && (p1.y >= x.y) && (x.y >= p2.y)) || ((p1.x <= x.x) && (x.x <= p2.x) && (p1.y <= x.y) && (x.y <= p2.y)))
		{
			return i + 1;
		}
	}
		return 0;
}


void IrregularPolygon::Resize_By_Drag(int point_number, Point old_point, Point new_point)
{
	Points[point_number - 1] = new_point;
}

void IrregularPolygon::Move(Point old_point, Point new_point)
{
	int diff_x = new_point.x - old_point.x;
	int diff_y = new_point.y - old_point.y;

	for (int i = 0; i < Points.size(); i++)
	{
		Points[i].x = Points[i].x + diff_x;
		Points[i].y = Points[i].y + diff_y;
	}
}

bool IrregularPolygon::IsPointInside(int x, int y)
{
	return false;
}


void IrregularPolygon::save_shape_points()
{
	for (int i = 0; i < Points.size(); i++)
	{
		shape_points.push_back(Points[i]);
	}
}
void IrregularPolygon::load_shape_points()
{
	for (int i = 0; i < shape_points.size(); i++)
	{
		Points[i] = shape_points[i];
	}
}
bool IrregularPolygon::is_shape_between_two_corners(Point p1, Point p2)
{
	for (int i = 0; i < Points.size(); i++)
	{
		if (is_point_inside_rect(p1,p2,Points[i]) == false)
		{
			return false;
		}
	}
	return true;
}

void IrregularPolygon::move_to_center(Point new_center)
{
	Point Center;

	int x_sum = 0;
	int y_sum = 0;
	for (auto temp : Points)
	{
		x_sum = x_sum + temp.x;
		y_sum = y_sum + temp.y;
	}

	Center.x = x_sum / Points.size();
	Center.y = y_sum / Points.size();

	int diff_x = new_center.x - Center.x;
	int diff_y = new_center.y - Center.y;

	for (int i = 0; i < Points.size(); i++)
	{
		Points[i].x = Points[i].x + diff_x;
		Points[i].y = Points[i].y + diff_y;
	}
}