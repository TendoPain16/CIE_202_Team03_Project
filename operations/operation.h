#pragma once
#include "..\DefS.h"
#include "..\GUI\GUI.h"

class controller; //forward class declaration



class operation	//Base class for all possible operations
{
protected:
	controller *pControl;		//operations needs control to do their job

public:
	operation(controller *pCont) { pControl = pCont; }	//constructor
	virtual ~operation() {}

	virtual void Execute() =0;	//Execute operation (code depends on operation type)
	//virtual void Undo()=0;	//To undo this operation (code depends on operation type)
	//virtual void Redo()=0;	//To redo this operation (code depends on operation type)

};

