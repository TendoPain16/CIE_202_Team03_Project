#include "Line.h"
#include <iostream>

Line::Line() {Corner1.x = 0; Corner1.y = 0; Corner2.x = 0; Corner2.y = 0;}


Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	Corner1 = P1;
	Corner2 = P2;
}



Line::~Line()
{}

void Line::Draw(GUI* pUI) const
{
	pUI->DrawLine(Corner1, Corner2, ShpGfxInfo);	//Call Output::Drawline to draw a line on the screen	
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


vector <shape*> Line::get_shapes_list()
{
	vector <shape*> null;
	return null;
}