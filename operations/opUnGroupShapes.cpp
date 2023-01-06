#include "opUnGroupShapes.h"
#include "..\shapes\Group.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include <typeinfo>
#include <iostream>

opUnGroupShapes::opUnGroupShapes(controller* pCont) :operation(pCont)
{}


opUnGroupShapes::~opUnGroupShapes()
{}


void opUnGroupShapes::Execute()		//Execute the operation
{
	
	Graph* pGr = pControl->getGraph();				//Get a pointer to the graph
	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces
	pGr->ungroup_shapes();
	pUI->PrintMessage("shapes has been seperate");

}
