#pragma once

#include "operation.h"

//Add opLoad operation class
class opLoad : public operation
{
public:
	opLoad(controller* pCont);
	virtual ~opLoad();

	//Add opLoad to the controller
	virtual void Execute();

};