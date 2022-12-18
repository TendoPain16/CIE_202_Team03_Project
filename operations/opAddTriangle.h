#pragma once
#include "operation.h"


class opAddTriangle : public operation		//Add Triangle operation class
{
public:
	opAddTriangle(controller* pCont);
	virtual ~opAddTriangle();

	virtual void Execute();			//Add Triangle to the controller
};

