#pragma once
#include "operation.h"


class opAddIrregularPolygon : public operation		//Add Rectangle operation class
{
public:
	opAddIrregularPolygon(controller* pCont);
	virtual ~opAddIrregularPolygon();

	virtual void Execute();			//Add rectangle to the controller
};

