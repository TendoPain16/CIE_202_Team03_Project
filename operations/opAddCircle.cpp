#include "opAddCircle.h"
#include "..\shapes\Circle.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opAddCircle::opAddCircle(controller* pCont) :operation(pCont)
{}


opAddCircle::~opAddCircle()
{}


void opAddCircle::Execute()		//Execute the operation
{
	Point P1, P2;

	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces

	pUI->PrintMessage("New Circle: Click at the center.");
	pUI->GetPointClicked(P1.x, P1.y);	//Read the center and store in point P1

	pUI->PrintMessage("The center is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )" + " ... Click at distance away from the center to be the radius.");
	pUI->GetPointClicked(P2.x, P2.y);	//Read radius and store in point P2
	
	pUI->ClearStatusBar();				

	//Preapre all circle parameters
	GfxInfo RectGfxInfo;
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.FillClr = pUI->getCrntFillColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	RectGfxInfo.image = "Empty";
	RectGfxInfo.isFilled = false;
	RectGfxInfo.isSelected = false;

	Circle* R = new Circle(P1, P2, RectGfxInfo);	//Create a circle with the above parameters

	Graph* pGr = pControl->getGraph();				//Get a pointer to the graph

	pGr->Addshape(R);								//Add the circle to the list of shapes
}
