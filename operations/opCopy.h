#pragma once

#include "operation.h"

//Add Move operation class
class opCopy : public operation
{
public:
	opCopy(controller* pCont);
	virtual ~opCopy();

	//Add Move to the controller
	virtual void Execute();

};