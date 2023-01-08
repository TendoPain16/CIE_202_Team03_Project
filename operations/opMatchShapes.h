#pragma once

#include "operation.h" 

//Add MatchShapes operation class

class opMatchShapes : public operation
{
public:
	opMatchShapes(controller* pCont);
	virtual ~opMatchShapes();

	virtual void Execute();
};