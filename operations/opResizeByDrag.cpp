
#include "opResizeByDrag.h"
#include "..\controller.h"

#include "..\GUI\GUI.h"

opResizeByDrag::opResizeByDrag(controller* pCont) :operation(pCont)
{}
opResizeByDrag::~opResizeByDrag()
{}

//Execute the operation
void opResizeByDrag::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    pGr->Resize_By_Drag(pUI);
    pUI->PrintMessage("resizing is off");
}

