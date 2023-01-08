#pragma once

#include "operation.h"

//Add opRestartGame operation class
class opRestartGame : public operation
{
public:
	opRestartGame(controller* pCont);
	virtual ~opRestartGame();

	//Add opRestartGame to the controller
	virtual void Execute();

};