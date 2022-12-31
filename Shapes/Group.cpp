#include "Group.h"

#include "Shape.h"
#include <fstream>
#include <vector>

#include <sstream>

#include "..\GUI\GUI.h"

#include "..\shapes\Square.h"
#include "..\shapes\Circle.h"
#include "..\shapes\Rect.h"
#include "..\Shapes\Triangle.h"
#include "..\shapes\Line.h"
#include "..\shapes\IrregularPolygon.h"
#include "..\shapes\RegularPolygon.h"

Group::Group() {}


Group::Group(vector <shape*> come, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	ID = Get_ID();
	groupshapesList = come;
	ShpGfxInfo.DrawClr = BLUE;
	ShpGfxInfo.FillClr = BLUE;
	ShpGfxInfo.BorderWdth = 3;
	ShpGfxInfo.image = "Empty";
	ShpGfxInfo.isFilled = false;
	ShpGfxInfo.isSelected = false;
}



Group::~Group()
{
	for (int i = 0; i < groupshapesList.size(); i++)
	{
		delete groupshapesList[i];
	}
}

void Group::Draw(GUI* pUI) const
{
	for (auto shapePointer : groupshapesList)
	{
		if (counter.dclr != 0)
			shapePointer->ChngDrawClr(ShpGfxInfo.DrawClr);
		if (counter.fclr != 0)
			shapePointer->ChngFillClr(ShpGfxInfo.FillClr);
		if (counter.bw != 0)
			shapePointer->ChngBorderWidth(ShpGfxInfo.BorderWdth);

		shapePointer->SetSelected(ShpGfxInfo.isSelected);
		if (counter.isfill != 0)
			shapePointer->SetFilled(ShpGfxInfo.isFilled);

		shapePointer->Draw(pUI);
	}
}

void Group::Save(ofstream& file) const
{
	file << "6" << "\t" << groupshapesList.size() << "\t" << ID << endl;
	for (auto shapePointer : groupshapesList)
		shapePointer->Save(file);
}


void Group::Load(vector <string> line, GUI* pUI, ifstream* inputfile)
{
	ID = stoi(line[2]);
	if (ID >= ID_gen)
		ID_gen = ID;
	groupshapesList.clear();

	int numberOfShapes = stoi(line[1]);

	string line_2;
	vector <string> wordsList;
	string var;
	for (int i = 0; i < numberOfShapes; i++)
	{
		getline(*inputfile, line_2);
		istringstream ss(line_2);
		wordsList.clear();
		while (ss >> var)
		{
			wordsList.push_back(var);
		}


		shape* R;
		switch (stoi(wordsList[0]))
		{
		case 0: R = new Rect(); break;
		case 1: R = new Square(); break;
		case 2: R = new Circle(); break;
		case 3: R = new Line(); break;
		case 4: R = new Triangle(); break;
		case 5: R = new IrregularPolygon(); break;
		case 6: R = new Group(); break;
		default: return;
		}

		R->Load(wordsList, pUI);
		groupshapesList.push_back(R);
	}

}


void Group::Resize(double number)
{
	for (auto shapePointer : groupshapesList)
		shapePointer->Resize(number);
}


vector <shape*> Group::get_shapes_list()
{
	return groupshapesList;
}