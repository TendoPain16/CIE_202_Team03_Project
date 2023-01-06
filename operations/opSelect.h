#pragma once

#include "operation.h" 

//Add Select operation class

class opSelect : public operation
{
public:
	opSelect(controller* pCont);
	virtual ~opSelect();

	//Execute action (code depends on action type)
	virtual void Execute();
};

