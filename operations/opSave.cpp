#include "opSave.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opSave::opSave(controller* pCont) :operation(pCont)
{}
opSave::~opSave()
{}

//Execute the operation
void opSave::Execute()
{
	GUI* pUI = pControl->GetUI();
	string name = pUI->GetSrting("name");
	ofstream info;
	info.open(name + ".txt");
	pControl->Save(info);
	info.close();
}
