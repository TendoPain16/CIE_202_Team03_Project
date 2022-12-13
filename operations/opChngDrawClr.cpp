#include "opChngDrawClr.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opChngDrawClr::opChngDrawClr(controller* pCont) :operation(pCont)
{}
opChngDrawClr::~opChngDrawClr()
{}

//Execute the operation
void opChngDrawClr::Execute()
{

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->ClearStatusBar();

	pUI->PrintMessage("pick a color");

	color temp = pUI->GetColor();

	pUI->PrintMessage("color has been selected");

	pUI->SetCrntDrawColor(temp);

}
