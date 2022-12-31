#pragma once
#include "operation.h"


class opUnGroupShapes : public operation	//Add UnGroupShapes operation class
{
public:
	opUnGroupShapes(controller* pCont);
	virtual ~opUnGroupShapes();

	virtual void Execute();		//Add UnGroupShapes to the controller
};

