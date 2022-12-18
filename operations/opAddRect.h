#pragma once

#include "operation.h"

class opAddRect: public operation		//Add Rectangle operation class
{
public:
	opAddRect(controller *pCont);
	virtual ~opAddRect();
	
	virtual void Execute() ;		//Add rectangle to the controller
};

