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

Group::Group(Group* x)
{
	int num = (x->groupshapesList).size();
	for (int i = 0; i < num; i++)
	{
		shape* temp = x->groupshapesList[i];
		if (dynamic_cast<Rect*> (temp))
		{
			Rect* x = dynamic_cast<Rect*> (temp);
			temp = new Rect(x);
		}
		else if (dynamic_cast<Square*> (temp))
		{
			Square* x = dynamic_cast<Square*> (temp);
			temp = new Square(x);
		}
		else if (dynamic_cast<Line*> (temp))
		{
			Line* x = dynamic_cast<Line*> (temp);
			temp = new Line(x);
		}
		else if (dynamic_cast<Triangle*> (temp))
		{
			Triangle* x = dynamic_cast<Triangle*> (temp);
			temp = new Triangle(x);
		}
		else if (dynamic_cast<Circle*> (temp))
		{
			Circle* x = dynamic_cast<Circle*> (temp);
			temp = new Circle(x);
		}
		else if (dynamic_cast<Group*> (temp))
		{
			Group* x = dynamic_cast<Group*> (temp);
			temp = new Group(x);
		}
		else if (dynamic_cast<IrregularPolygon*> (temp))
		{
			IrregularPolygon* x = dynamic_cast<IrregularPolygon*> (temp);
			temp = new IrregularPolygon(x);
		}
		(this->groupshapesList).push_back(temp);
	}
	this->resizing = x->resizing;
	this->ShpGfxInfo = x->ShpGfxInfo;
	this->ID = x->ID;
}

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

int Group::is_on_corners(Point x)
{
	if (true)
	{

	}
	else
		return 0;
}

void Group::Resize_By_Drag(int point_number, Point old_point, Point new_point)
{

}

void Group::Move(Point old_point, Point new_point)
{
	for (auto shapePointer : groupshapesList)
		shapePointer->Move(old_point,new_point);
}


vector <shape*> Group::get_shapes_list()
{
	return groupshapesList;
}

bool Group::IsPointInside(int x, int y)
{
	Point upper_right_corner;
	Point bottom_left_corner;

	for (int i = 0; i < groupshapesList.size(); i++)
	{
		if (groupshapesList[i]->IsPointInside(x,y))
		{
			return true;
		}
	}
	return false;
}

void Group::save_shape_points()
{

}
void Group::load_shape_points()
{

}
bool Group::is_shape_between_two_corners(Point p1, Point p2)
{
	return true;
}

void Group::move_to_center(Point new_center)
{

}