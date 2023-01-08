#include "opExit.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Circle.h"

opExit::opExit(controller* pCont) :operation(pCont)
{}
opExit::~opExit()
{}


//Execute the operation
void opExit::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGr = pControl->getGraph();

	pGr->Exit(pUI);

}



/*


bool opExit::Execute()
{
	GUI* pUI = pControl->getUI();

	pUI->PrintMessage("Do want to leave?! 'yes' or 'y' to exit : ");
	string leave = pGUI->GetSrting();  

	if (leave == "y" || leave == "yes")
	{
		exit(-1);
	}
	else
	{

	}

	return true;
}

*/