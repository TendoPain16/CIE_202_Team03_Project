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
	
	Graph* pGr = pControl->getGraph();				//Get a pointer to the graph
	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces
	
	vector <shape*> ListOfShapes = pGr->group_shapes();

	pUI->PrintMessage("shapes has been in group");

	//Preapre all circle parameters
	GfxInfo RectGfxInfo;
	RectGfxInfo.DrawClr;
	RectGfxInfo.FillClr;
	RectGfxInfo.BorderWdth;
	RectGfxInfo.image;
	RectGfxInfo.isFilled;
	RectGfxInfo.isSelected;

	
	
	Group* R = new Group(ListOfShapes, RectGfxInfo);	//Create a circle with the above parameters
	pGr->Addshape(R);								//Add the circle to the list of shapes
}
