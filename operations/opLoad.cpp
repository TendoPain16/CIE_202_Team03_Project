#include "opLoad.h"

#include "..\controller.h"

#include "..\GUI\GUI.h"

opLoad::opLoad(controller* pCont) :operation(pCont)
{}
opLoad::~opLoad()
{}

//Execute the operation
void opLoad::Execute()
{
	GUI* pUI = pControl->GetUI();
	string name = pUI->GetSrting("Please enter the file name: ");
	ifstream info;
	info.open(name + ".txt");
	pControl->Load(info);
	info.close();

}

