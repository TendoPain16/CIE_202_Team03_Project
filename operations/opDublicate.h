#pragma once

#include "operation.h"

//Add opDublicate operation class
class opDublicate : public operation
{
public:
	opDublicate(controller* pCont);
	virtual ~opDublicate();

	//Add opDublicate to the controller
	virtual void Execute();

};