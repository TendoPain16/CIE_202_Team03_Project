#pragma once

#include "operation.h"

//Add Circle operation class
class opSelectShape : public operation
{
public:
	opSelectShape(controller* pCont);
	virtual ~opSelectShape();

	virtual void Execute();

};

