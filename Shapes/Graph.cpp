#include <sstream>

#include "Graph.h"
#include "..\GUI\GUI.h"

#include "..\shapes\Square.h"
#include "..\shapes\Circle.h"
#include "..\shapes\Rect.h"
#include "..\Shapes\Triangle.h"
#include "..\shapes\Line.h"
#include "..\shapes\IrregularPolygon.h"
#include "..\shapes\RegularPolygon.h"


Graph::Graph() {selectedShape = nullptr;}

Graph::~Graph() {}



//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//
void Graph::Addshape(shape* pShp)	//Add a shape to the list of shapes
{
	shapesList.push_back(pShp);		//Add a new shape to the shapes vector
}


void Graph::Draw(GUI* pUI) const	//Draw all shapes on the user interface
{
	pUI->ClearDrawArea();
	for (auto shapePointer : shapesList)
		shapePointer->Draw(pUI);	
}


shape* Graph::Getshape(int x, int y) const
{
	//If a shape is found return a pointer to it.
	//if this point (x,y) does not belong to any shape return NULL

	///Add your code here to search for a shape given a point x,y	
	return nullptr;
}


void Graph::Clear_shapeslist()
{shapesList.clear();}


void Graph::Save(ofstream& outfile) 
{	
	for (auto shapePointer : shapesList)
		shapePointer->Save(outfile);
}


void Graph::Load(ifstream& inputfile, GUI* pUI)
{
	pUI->ClearDrawArea();
	shapesList.clear();

	string line;
	vector <string> wordsList;
	string var;
	while (getline(inputfile, line))
	{
		istringstream ss(line);
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
		default: return;
		}

		R->Load(wordsList, pUI);
		Addshape(R);
	}
}