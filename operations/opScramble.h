#pragma once

#include "operation.h" 

//Add Scramble operation class

class opScramble : public operation
{
public:
	opScramble(controller* pCont);
	virtual ~opScramble();

	virtual void Execute();
};