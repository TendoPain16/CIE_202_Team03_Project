#pragma once

#include "operation.h"

//Add Resize operation class
class opResizeByDrag : public operation
{
public:
	opResizeByDrag(controller* pCont);
	virtual ~opResizeByDrag();

	//Add Resize to the controller
	virtual void Execute();

};
