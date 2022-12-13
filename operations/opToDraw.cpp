
#include "opToDraw.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"

opToDraw::opToDraw(controller* pCont) :operation(pCont)
{}
opToDraw::~opToDraw()
{}

//Execute the operation
void opToDraw::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();
	pUI->SetCrntMode(MODE_DRAW);
	pUI->ClearStatusBar();
	pUI->ClearDrawArea();
	pUI->CreateDrawToolBar();
	pUI->PrintMessage("Welcome To Draw Mode ^_^");
}
