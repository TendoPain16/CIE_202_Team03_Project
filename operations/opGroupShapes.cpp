#include "opGroupShapes.h"
#include "..\shapes\Group.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opGroupShapes::opGroupShapes(controller* pCont) :operation(pCont)
{}


opGroupShapes::~opGroupShapes()
{}


void opGroupShapes::Execute()		//Execute the operation
{
	Graph* pGr = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	
	pGr->group_shapes();

	pUI->PrintMessage("shapes has been in group");

}
