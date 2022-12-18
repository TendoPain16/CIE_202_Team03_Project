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


void Triangle::Load(vector <string> line, GUI* pUI)
{
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