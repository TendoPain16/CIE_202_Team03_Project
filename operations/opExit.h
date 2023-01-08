#pragma once
#include "operation.h"
//Class responsible for adding course action
class opExit : public operation
{

public:
	opExit(controller* pCont);
	virtual ~opExit();

	//Add Move to the controller
	virtual void Execute();

};