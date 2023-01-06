
#include "opToPlay.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"

opToPlay::opToPlay(controller* pCont) :operation(pCont)
{}
opToPlay::~opToPlay()
{}

//Execute the operation
void opToPlay::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();
	pUI->SetCrntMode(MODE_PLAY);
	pUI->ClearStatusBar();
	pUI->ClearDrawArea();
	pUI->CreatePlayToolBar();
	pUI->PrintMessage("Welcome To Play Mode ^_^");
}
