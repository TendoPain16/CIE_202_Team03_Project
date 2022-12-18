#include "opAddTriangle.h"
#include "..\shapes\Triangle.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opAddTriangle::opAddTriangle(controller* pCont) :operation(pCont)
{}


opAddTriangle::~opAddTriangle()
{}


void opAddTriangle::Execute()				//Execute the operation
{
	Point P1, P2, P3;

	GUI* pUI = pControl->GetUI();			//Get a Pointer to the Input / Output Interfaces

	pUI->PrintMessage("New Triangle: Click at first corner");
	pUI->GetPointClicked(P1.x, P1.y);		//Read 1st corner and store in point P1


	pUI->PrintMessage("First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )" + " ... Click at second corner");
	pUI->GetPointClicked(P2.x, P2.y);		//Read 2nd corner and store in point P2


	pUI->PrintMessage("Second corner is at (" + to_string(P2.x) + ", " + to_string(P2.y) + " )" + " ... Click at third corner");
	pUI->GetPointClicked(P3.x, P3.y);		//Read 3nd corner and store in point P3

	pUI->ClearStatusBar();

	//Preapre all Triangle parameters
	GfxInfo RectGfxInfo;
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.FillClr = pUI->getCrntFillColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	RectGfxInfo.image = "Empty";
	RectGfxInfo.isFilled = false;
	RectGfxInfo.isSelected = false;

	Triangle* R = new Triangle(P1, P2,P3, RectGfxInfo);	//Create a Triangle with the above parameters

	Graph* pGr = pControl->getGraph();					//Get a pointer to the graph

	pGr->Addshape(R);									//Add the Triangle to the list of shapes
}
