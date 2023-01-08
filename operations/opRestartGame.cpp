#include "opRestartGame.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opRestartGame::opRestartGame(controller* pCont) :operation(pCont)
{}
opRestartGame::~opRestartGame()
{}

//Execute the operation
void opRestartGame::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();


	pGr->Restart_Game(pUI);
	pUI->PrintMessage("Restarted");
}