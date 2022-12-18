#pragma once
#include "operation.h"


class opAddLine : public operation		//Add line operation class
{
public:
	opAddLine(controller* pCont);
	virtual ~opAddLine();

	virtual void Execute();		//Add line to the controller
};

