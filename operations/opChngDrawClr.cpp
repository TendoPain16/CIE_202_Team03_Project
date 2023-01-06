#include "opChngDrawClr.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opChngDrawClr::opChngDrawClr(controller* pCont) :operation(pCont)
{}


opChngDrawClr::~opChngDrawClr()
{}


void opChngDrawClr::Execute()		//Execute the operation
{
	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces
	Graph* pGr = pControl->getGraph();

	color temp = pUI->GetColor();
	pUI->ClearStatusBar();
	pUI->PrintMessage("pick a color");
	pUI->PrintMessage("color has been selected");

	pGr->change_draw_clr(pUI, temp);
}
