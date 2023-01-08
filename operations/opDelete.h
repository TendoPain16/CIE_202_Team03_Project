#pragma once

#include "operation.h"

//Add Move operation class
class opDelete : public operation
{
public:
	opDelete(controller* pCont);
	virtual ~opDelete();

	//Add Move to the controller
	virtual void Execute();

};