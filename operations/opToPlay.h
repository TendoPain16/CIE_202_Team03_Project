#pragma once

#include "operation.h"

//Add To_Play operation class
class opToPlay : public operation
{
public:
	opToPlay(controller* pCont);
	virtual ~opToPlay();

	//Add To_Play to the controller
	virtual void Execute();

};