#include "Circle.h"

Circle::Circle()
{
	Center.x = 0;
	Center.y = 0;
	Radius.x = 0;
	Radius.y = 0;
}

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
}

void Circle::Save(ofstream& file) const
{
	file << 2 << "\t" << "Circle" << "\t" << ID << "\t" << int(ShpGfxInfo.DrawClr.ucRed) << "\t" << int(ShpGfxInfo.DrawClr.ucGreen) << "\t" << int(ShpGfxInfo.DrawClr.ucBlue) << "\t";
	
	if (ShpGfxInfo.isFilled)
		file << int(ShpGfxInfo.FillClr.ucRed) << "\t" << int(ShpGfxInfo.FillClr.ucGreen) << "\t" << int(ShpGfxInfo.FillClr.ucBlue);
	else
		file << "NotFilled" << "\t" << "NotFilled" << "\t" << "NotFilled";
	
	file << "\t" << ShpGfxInfo.BorderWdth << "\t" << ShpGfxInfo.image << "\t" << Center.x << "\t" << Center.y << "\t" << Radius.x << "\t" << Radius.y << endl;
	
}

void Circle::Load(vector <string> line, GUI* pUI)
{
	ShpGfxInfo.DrawClr = color(stoi(line[3]), stoi(line[4]), stoi(line[5]));
	ShpGfxInfo.isFilled = false;
	ShpGfxInfo.isSelected = false;


	if (line[6] != "NotFilled")

	{
		ShpGfxInfo.isFilled = true;
		ShpGfxInfo.FillClr = color(stoi(line[6]), stoi(line[7]), stoi(line[8]));
	}

	ShpGfxInfo.BorderWdth = stoi(line[9]);
	ShpGfxInfo.image = line[10];

	Center.x = stoi(line[11]);
	Center.y = stoi(line[12]);
	Radius.x = stoi(line[13]);
	Radius.y = stoi(line[14]);
}