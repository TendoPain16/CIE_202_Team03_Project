#include "opDublicate.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opDublicate::opDublicate(controller* pCont) :operation(pCont)
{}
opDublicate::~opDublicate()
{}

//Execute the operation
void opDublicate::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	pGr->Dublicate();
	pUI->PrintMessage("Dublicated");


}
