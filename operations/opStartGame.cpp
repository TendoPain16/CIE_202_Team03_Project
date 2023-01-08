#include "opStartGame.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opStartGame::opStartGame(controller* pCont) :operation(pCont)
{}
opStartGame::~opStartGame()
{}

//Execute the operation
void opStartGame::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	pGr->Start_Game();

}