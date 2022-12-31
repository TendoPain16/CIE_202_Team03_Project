#pragma once
#include "operation.h"


class opGroupShapes : public operation	//Add GroupShapes operation class
{
public:
	opGroupShapes(controller* pCont);
	virtual ~opGroupShapes();

	virtual void Execute();		//Add GroupShapes to the controller
};

