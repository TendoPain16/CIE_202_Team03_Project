#include "opAddRect.h"
#include "..\shapes\Rect.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opAddRect::opAddRect(controller * pCont):operation(pCont)
{}


opAddRect::~opAddRect()
{} 


void opAddRect::Execute()	 //Execute the operation
{
	Point P1, P2;

	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces

	pUI->PrintMessage("New Rectangle: Click at first corner");
	pUI->GetPointClicked(P1.x, P1.y);	//Read 1st corner and store in point P1

	pUI->PrintMessage("First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )" + " ... Click at second corner");
	pUI->GetPointClicked(P2.x, P2.y);	//Read 2nd corner and store in point P2

	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo RectGfxInfo;
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.FillClr = pUI->getCrntFillColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	RectGfxInfo.image = "Empty";
	RectGfxInfo.isFilled = false;
	RectGfxInfo.isSelected = false;

	Rect *R=new Rect(P1, P2, RectGfxInfo);	//Create a rectangle with the above parameters

	Graph* pGr = pControl->getGraph();		//Get a pointer to the graph

	pGr->Addshape(R);						//Add the rectangle to the list of shapes
}
