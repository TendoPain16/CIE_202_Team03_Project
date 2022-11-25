#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddSquare : public operation
{
public:
	opAddSquare(controller* pCont);
	virtual ~opAddSquare();

	//Add rectangle to the controller
	virtual void Execute();

};

