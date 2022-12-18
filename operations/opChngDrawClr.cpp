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

	pUI->ClearStatusBar();

	pUI->PrintMessage("pick a color");

	color temp = pUI->GetColor();

	pUI->PrintMessage("color has been selected");

	pUI->SetCrntDrawColor(temp);
}
