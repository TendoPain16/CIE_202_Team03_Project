#pragma once

#include "operation.h"

//Add opStartGame operation class
class opStartGame : public operation
{
public:
	opStartGame(controller* pCont);
	virtual ~opStartGame();

	//Add opStartGame to the controller
	virtual void Execute();

};