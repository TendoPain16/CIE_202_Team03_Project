#include "Square.h"

Square::Square()
{
	Corner1.x = 0;
	Corner1.y = 0;
	Corner2.x = 0;
	Corner2.y = 0;
}

Square::Square(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	Corner1 = P1;
	Corner2 = P2;
}

Square::~Square()
{}

void Square::Draw(GUI* pUI) const
{
	//Call Output::DrawSQUA to draw a square on the screen	
	pUI->DrawSquare(Corner1, Corner2, ShpGfxInfo);
}

void Square::Save(ofstream& file) const
{
	file << 1 << "\t" << "Square" << "\t" << ID << "\t" << int(ShpGfxInfo.DrawClr.ucRed) << "\t" << int(ShpGfxInfo.DrawClr.ucGreen) << "\t" << int(ShpGfxInfo.DrawClr.ucBlue) << "\t";

	if (ShpGfxInfo.isFilled)
		file << int(ShpGfxInfo.FillClr.ucRed) << "\t" << int(ShpGfxInfo.FillClr.ucGreen) << "\t" << int(ShpGfxInfo.FillClr.ucBlue);
	else
		file << "NotFilled" << "\t" << "NotFilled" << "\t" << "NotFilled";

	file << "\t" << ShpGfxInfo.BorderWdth << "\t" << ShpGfxInfo.image << "\t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << endl;

}

void Square::Load(vector <string> line, GUI* pUI)
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

	Corner1.x = stoi(line[11]);
	Corner1.y = stoi(line[12]);
	Corner2.x = stoi(line[13]);
	Corner2.y = stoi(line[14]);
}