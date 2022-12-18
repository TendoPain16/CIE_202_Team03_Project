#pragma once
#include "operation.h"


class opAddCircle : public operation	//Add Circle operation class
{
public:
	opAddCircle(controller* pCont);
	virtual ~opAddCircle();

	virtual void Execute();		//Add circle to the controller
};

