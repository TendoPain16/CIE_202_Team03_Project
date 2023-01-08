#pragma once

#include "operation.h"

//Add Move operation class
class opPaste : public operation
{
public:
	opPaste(controller* pCont);
	virtual ~opPaste();

	//Add Move to the controller
	virtual void Execute();

};