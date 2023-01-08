#include "opMatchShapes.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "opSelect.h"

using namespace std;


opMatchShapes::opMatchShapes(controller* pCont) :operation(pCont)
{}
opMatchShapes::~opMatchShapes()
{}

//Execute the operation

void opMatchShapes::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	pGr->Matsh_Shapes(pUI);
}
