
#include "opResize.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"

opResize::opResize(controller* pCont) :operation(pCont)
{}
opResize::~opResize()
{}

//Execute the operation
void opResize::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	string scale = pUI->GetSrting("Please choose size scale (0.25 , 0.5 , 2 , 4): ");
	double number = stod(scale);

	pGr->resize(number);

}
