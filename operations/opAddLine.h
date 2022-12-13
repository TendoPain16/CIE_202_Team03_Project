#pragma once

#include "operation.h"

//Add line operation class
class opAddLine : public operation
{
public:
	opAddLine(controller* pCont);
	virtual ~opAddLine();

	//Add line to the controller
	virtual void Execute();

};

