#pragma once

#include "operation.h"

//Add ChngDrawClr operation class
class opChngDrawClr : public operation
{
public:
	opChngDrawClr(controller* pCont);
	virtual ~opChngDrawClr();

	//Add ChngDrawClr to the controller
	virtual void Execute();

};
