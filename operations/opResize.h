#pragma once

#include "operation.h"

//Add Resize operation class
class opResize : public operation
{
public:
	opResize(controller* pCont);
	virtual ~opResize();

	//Add Resize to the controller
	virtual void Execute();

};