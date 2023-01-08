#include "opPaste.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Circle.h"

opPaste::opPaste(controller* pCont) :operation(pCont)
{}
opPaste::~opPaste()
{}


//Execute the operation
void opPaste::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    pGr->Paste(pUI);

    pUI->PrintMessage("shape is pasted");
}
