#include "opAddLine.h"
#include "..\shapes\Line.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"


opAddLine::opAddLine(controller* pCont) :operation(pCont)
{}


opAddLine::~opAddLine()
{}


void opAddLine::Execute()
{
	
	Point P1, P2;

	GUI* pUI = pControl->GetUI();	
	Graph* pGr = pControl->getGraph();

	pUI->PrintMessage("New Line: Click at first corner");
	pUI->GetPointClicked(P1.x, P1.y);

	pUI->PrintMessage("First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )" + " ... Click at second corner");
	pUI->GetPointClicked(P2.x, P2.y);

	pUI->ClearStatusBar();

	GfxInfo RectGfxInfo;
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.FillClr = pUI->getCrntFillColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();
	RectGfxInfo.image = "Empty";
	RectGfxInfo.isFilled = false;
	RectGfxInfo.isSelected = false;

	Line* R = new Line(P1, P2, RectGfxInfo);
	pGr->Addshape(R);

}
