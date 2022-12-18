#pragma once
#include "operation.h"


class opAddSquare : public operation		//Add Square operation class
{
public:
	opAddSquare(controller* pCont);
	virtual ~opAddSquare();

	virtual void Execute();		//Add square to the controller
};

