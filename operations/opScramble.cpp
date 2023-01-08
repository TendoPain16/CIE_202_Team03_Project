#include "opScramble.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "opSelect.h"

using namespace std;


opScramble::opScramble(controller* pCont) :operation(pCont)
{}
opScramble::~opScramble()
{}

//Execute the operation

void opScramble::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	pGr->Scramble();
	pUI->PrintMessage("Done");
}
