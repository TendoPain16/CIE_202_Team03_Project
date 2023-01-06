#include "opSelect.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "opSelect.h"

using namespace std;


opSelect::opSelect(controller* pCont) :operation(pCont)
{}
opSelect::~opSelect()
{}

//Execute the operation

void opSelect::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	action temp = pUI->Get_current_action_info();
	pGr->select(temp);

	pUI->ClearStatusBar();
}
