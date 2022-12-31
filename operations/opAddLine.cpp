#include "opAddLine.h"
#include "..\shapes\Line.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opAddLine::opAddLine(controller* pCont) :operation(pCont)
{}


opAddLine::~opAddLine()
{}


void opAddLine::Execute()						//Execute the operation
{
	
	Point P1, P2;

	GUI* pUI = pControl->GetUI();				//Get a Pointer to the Input / Output Interfaces
	Graph* pGr = pControl->getGraph();			//Get a pointer to the graph
	/*
	pUI->PrintMessage("New Line: Click at first corner");
	pUI->GetPointClicked(P1.x, P1.y);			//Read 1st corner and store in point P1

	pUI->PrintMessage("First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )" + " ... Click at second corner");
	pUI->GetPointClicked(P2.x, P2.y);			//Read 2nd corner and store in point P2

	pUI->ClearStatusBar();

	//Preapre all line parameters
	GfxInfo RectGfxInfo;
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.FillClr = pUI->getCrntFillColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	RectGfxInfo.image = "Empty";
	RectGfxInfo.isFilled = false;
	RectGfxInfo.isSelected = false;

	Line* R = new Line(P1, P2, RectGfxInfo);	//Create a line with the above parameters

	

	pGr->Addshape(R);							//Add the line to the list of shapes
	*/

	int id = stoi(pUI->GetSrting("enter id: "));
	vector <shape*> list = pGr->GetShapesList();
	for (auto s : list)
	{
		if (s->Get_current_ID()  == id)
		{
			if (s->IsSelected() == true)
				s->SetSelected(false);
			else
				s->SetSelected(true);
		}
	}
}
