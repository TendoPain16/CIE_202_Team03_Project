#include "opAddIrregularPolygon.h"
#include "..\shapes\IrregularPolygon.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opAddIrregularPolygon::opAddIrregularPolygon(controller* pCont) :operation(pCont)
{}


opAddIrregularPolygon::~opAddIrregularPolygon()
{}


void opAddIrregularPolygon::Execute()	//Execute the operation
{
	GUI* pUI = pControl->GetUI();	//Get a Pointer to the Input / Output Interfaces

	pUI->ClearStatusBar();
	string Vertices = pUI->GetSrting("New IrregularPolygon: Please enter vertices number: ");
	vector <Point> Points;
	
	pUI->PrintMessage("Please click at the points.");

	string msg;
	int x;
	int y;
	Point temp;
	for (int i = 0; i < stoi(Vertices); i++)
	{
		pUI->GetPointClicked(temp.x, temp.y);
		Points.push_back(temp);

		msg = "Point clicked at (" + to_string(Points[i].x) + ", " + to_string(Points[i].y) + " )";

		if (i == stoi(Vertices) - 1)
		{
			msg += " all points has been clicked.";
		}
		pUI->PrintMessage(msg);
	}

	//Preapre all IrregularPolygon parameters
	GfxInfo IrregpolGfxInfo;
	IrregpolGfxInfo.DrawClr = pUI->getCrntDrawColor();
	IrregpolGfxInfo.FillClr = pUI->getCrntFillColor();
	IrregpolGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	IrregpolGfxInfo.image = "Empty";
	IrregpolGfxInfo.isFilled = false;
	IrregpolGfxInfo.isSelected = false;

	IrregularPolygon* R = new IrregularPolygon(Points, stoi(Vertices), IrregpolGfxInfo);	//Create a IrregularPolygon with the above parameters

	Graph* pGr = pControl->getGraph();														//Get a pointer to the graph

	pGr->Addshape(R);																		//Add the IrregularPolygon to the list of shapes
}
