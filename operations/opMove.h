#pragma once

#include "operation.h"

//Add Move operation class
class opMove : public operation
{
public:
	opMove(controller* pCont);
	virtual ~opMove();

	//Add Move to the controller
	virtual void Execute();

};