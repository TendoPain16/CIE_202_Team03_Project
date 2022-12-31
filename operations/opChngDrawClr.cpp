#include "opChngDrawClr.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opChngDrawClr::opChngDrawClr(controller* pCont) :operation(pCont)
{}


opChngDrawClr::~opChngDrawClr()
{}


void opChngDrawClr::Execute()		//Execute the operation
{
	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces
	Graph* pGr = pControl->getGraph();
	vector <shape*> ShapesList = pGr->GetShapesList();

	color temp = pUI->GetColor();
	pUI->ClearStatusBar();
	pUI->PrintMessage("pick a color");
	pUI->PrintMessage("color has been selected");

	int counter = 0;
	for (int i = 0; i < ShapesList.size(); i++)
	{
		if (ShapesList[i]->IsSelected())
		{
			ShapesList[i]->ChngFillClr(temp);
			counter++;
		}
	}

	if (counter != 0)
		return;

	pUI->SetCrntDrawColor(temp);
}
