#pragma once
#include "operation.h"


class opChngDrawClr : public operation		//Add ChngDrawClr operation class
{
public:
	opChngDrawClr(controller* pCont);
	virtual ~opChngDrawClr();

	virtual void Execute();		//Add ChngDrawClr to the controller
};
