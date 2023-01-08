#pragma once
#include "operation.h"


class opChngFillClr : public operation		//Add ChngDrawClr operation class
{
public:
	opChngFillClr(controller* pCont);
	virtual ~opChngFillClr();

	virtual void Execute();		//Add ChngDrawClr to the controller
};
