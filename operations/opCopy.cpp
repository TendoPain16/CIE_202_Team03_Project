
#include "opCopy.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Circle.h"

opCopy::opCopy(controller* pCont) :operation(pCont)
{}
opCopy::~opCopy()
{}


//Execute the operation
void opCopy::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    pGr->Copy(pUI);

    pUI->PrintMessage("shape is copied");
}
