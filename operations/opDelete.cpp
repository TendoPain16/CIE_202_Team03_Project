#include "opDelete.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include "..\Shapes\Circle.h"

opDelete::opDelete(controller* pCont) :operation(pCont)
{}
opDelete::~opDelete()
{}


//Execute the operation
void opDelete::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGr = pControl->getGraph();

    pGr->Delete(pUI);

    
}
