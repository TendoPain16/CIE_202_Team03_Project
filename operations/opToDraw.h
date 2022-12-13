#pragma once

#include "operation.h"

//Add opToDraw operation class
class opToDraw : public operation
{
public:
	opToDraw(controller* pCont);
	virtual ~opToDraw();

	//Add opToDraw to the controller
	virtual void Execute();

};