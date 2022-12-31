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


IrregularPolygon::~IrregularPolygon()
{}

void IrregularPolygon::Draw(GUI* pUI) const
{
	pUI->DrawIrregularpolygon(Points, V_number, ShpGfxInfo);	//Call Output::DrawIrregularPolygon to draw a IrregulatPolygon on the screen
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


vector <shape*> IrregularPolygon::get_shapes_list()
{
	vector <shape*> null;
	return null;
}