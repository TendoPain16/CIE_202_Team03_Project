#include "opAddSquare.h"
#include "..\shapes\Square.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opAddSquare::opAddSquare(controller* pCont) :operation(pCont)
{}


opAddSquare::~opAddSquare()
{}


void opAddSquare::Execute()		//Execute the operation
{
	Point P1, P2;

	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces

	pUI->PrintMessage("New Square: Click at first corner");
	pUI->GetPointClicked(P1.x, P1.y);	//Read 1st corner and store in point P1

	pUI->PrintMessage("First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )" + " ... Click at the lenght you want");
	pUI->GetPointClicked(P2.x, P2.y);	//Read the length and store in point P2
	
	pUI->ClearStatusBar();

	//Preapre all square parameters
	GfxInfo RectGfxInfo;
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.FillClr = pUI->getCrntFillColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	RectGfxInfo.image = "Empty";
	RectGfxInfo.isFilled = false;
	RectGfxInfo.isSelected = false;

	Square* R = new Square(P1, P2, RectGfxInfo);	//Create a square with the above parameters

	Graph* pGr = pControl->getGraph();				//Get a pointer to the graph

	pGr->Addshape(R);								//Add the square to the list of shapes


}
