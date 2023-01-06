
#include "opMove.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Circle.h"

opMove::opMove(controller* pCont) :operation(pCont)
{}
opMove::~opMove()
{}


//Execute the operation
void opMove::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    pGr->move_shapes(pUI);
    pUI->PrintMessage("move is off");
}
