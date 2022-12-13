#pragma once

#include "operation.h"
#include <fstream>

//Add opSave operation class
class opSave : public operation
{
public:
	opSave(controller* pCont);
	virtual ~opSave();

	//Add opSave to the controller
	virtual void Execute();

};