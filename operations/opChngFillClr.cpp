#include "opChngFillClr.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opChngFillClr::opChngFillClr(controller* pCont) :operation(pCont)
{}


opChngFillClr::~opChngFillClr()
{}


void opChngFillClr::Execute()		//Execute the operation
{
	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces
	Graph* pGr = pControl->getGraph();

	color temp = pUI->GetColor();
	pUI->ClearStatusBar();
	pUI->PrintMessage("pick a color");
	pUI->PrintMessage("color has been selected");

	pGr->change_fill_clr(pUI, temp);
}
