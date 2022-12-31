#include "opUnGroupShapes.h"
#include "..\shapes\Group.h"
#include "..\controller.h"
#include "..\GUI\GUI.h"
#include <typeinfo>
#include <iostream>

opUnGroupShapes::opUnGroupShapes(controller* pCont) :operation(pCont)
{}


opUnGroupShapes::~opUnGroupShapes()
{}


void opUnGroupShapes::Execute()		//Execute the operation
{
	
	Graph* pGr = pControl->getGraph();				//Get a pointer to the graph
	GUI* pUI = pControl->GetUI();		//Get a Pointer to the Input / Output Interfaces
	
	vector <shape*> ListOfShapes = pGr->GetShapesList();
	string temp;
	for (int i = 0; i < ListOfShapes.size(); i++)
	{
		temp = typeid(*(ListOfShapes[i])).name();
		if ((temp == "class Group") && (ListOfShapes[i]->IsSelected() == true))
		{
			vector <shape*> temp_list = ListOfShapes[i]->get_shapes_list();
			for (int i = 0; i < temp_list.size(); i++)
			{
				temp_list[i]->SetSelected(false);
				ListOfShapes.push_back(temp_list[i]);
			}
			ListOfShapes.erase(ListOfShapes.begin() + i);
		}
	}

	for (int i = 0; i < ListOfShapes.size(); i++)
	{
		for (int j = i + 1; j < ListOfShapes.size(); j++)
		{
			if (ListOfShapes[i] > ListOfShapes[j])
			{
				shape* temp = ListOfShapes[i];
				ListOfShapes[i] = ListOfShapes[j];
				ListOfShapes[j] = temp;
			}
		}
	}

	pGr->SetShapesList(ListOfShapes);

	pUI->PrintMessage("shapes has been seperate");

}
