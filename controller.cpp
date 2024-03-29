#include "controller.h"
#include "operations\opAddRect.h"
#include "operations\opAddCircle.h"
#include "operations\opAddSquare.h"
#include "operations\opAddLine.h"
#include "operations\opAddTriangle.h"
#include "operations\opAddIrregularPolygon.h"
#include "operations\opChngDrawClr.h"
#include "operations\opSelect.h"
#include "operations\opChngFillClr.h"
#include "operations\opDelete.h"
#include "operations\opCopy.h"
#include "operations\opPaste.h"
#include "operations\opExit.h"
#include "operations\opScramble.h"
//#include "operations\opHide.h"
//#include "operations\opUnhide.h"
#include "operations\opMatchShapes.h"
#include "operations\opMove.h"
#include "operations\opResizeByDrag.h"
#include "operations\opStartGame.h"
#include "operations\opRestartGame.h"
#include "operations\opDublicate.h"
#include "operations\opToPlay.h"
#include "operations\opToDraw.h"
#include "operations\opSave.h"
#include "operations\opLoad.h"
#include "operations\opResize.h"
#include "operations\opGroupShapes.h"
#include "operations\opUnGroupShapes.h"



//==================================================================================//
//									Constructor										//
//==================================================================================//
controller::controller()
{
	pGraph = new Graph;
	pGUI = new GUI;			//Create GUI object
}



//==================================================================================//
//							operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation()	//Ask the input to get the operation from the user.
{
	return pGUI->GetUseroperation();		
}


operation* controller::createOperation(operationType OpType)	//Creates an operation and executes it
{
	operation* pOp = nullptr;
	
	switch (OpType)		//According to operation Type, create the corresponding operation object
	{
	case DRAW_RECT:
		pOp = new opAddRect(this);
		break;

	case DRAW_LINE:
		pOp = new opAddLine(this);
		break;

	case DRAW_IRREGPOL:
		pOp = new opAddIrregularPolygon(this);
		break;

	case DRAW_TRIA:
		pOp = new opAddTriangle(this);
		break;

	case DRAW_CIRC:
		pOp = new opAddCircle(this);
		break;

	case DRAW_SQUA:
		pOp = new opAddSquare(this);
		break;

	case CHNG_DRAW_CLR:
		pOp = new opChngDrawClr(this);
		break;

	case CHNG_FILL_CLR:
		pOp = new opChngFillClr(this);
		break;

	case SELECT:
		pOp = new opSelect(this);
		break;

	case DEL:
		pOp = new opDelete(this);
		break;

	case TO_PLAY:
		pOp = new opToPlay(this);
		break;

	case TO_DRAW:
		pOp = new opToDraw(this);
		break;

	case SAVE:
		pOp = new opSave(this);
		break;

	case LOAD:
		pOp = new opLoad(this);
		break;

	case RESIZE:
		pOp = new opResize(this);
		break;

	case MOVE:
		pOp = new opMove(this);
		break;

	case COPY:
		pOp = new opCopy(this);
		break;

	case PASTE:
		pOp = new opPaste(this);
		break;

	case DUPLICAT:
		pOp = new opDublicate(this);
		break;

	case SCRAMBLE:
		pOp = new opScramble(this);
		break;

	case RESIZE_BY_DRAG:
		pOp = new opResizeByDrag(this);
		break;

	case GROUP_SHAPES:
		pOp = new opGroupShapes(this);
		break;

	case UN_GROUP_SHAPES:
		pOp = new opUnGroupShapes(this);
		break;

	case EXIT:
		pOp = new opExit(this);
		break;

	case START_GAME:
		pOp = new opStartGame(this);
		break;

	case RESTART_GAME:
		pOp = new opRestartGame(this);
		break;

	case HIDE:
	//	pOp = new opHide(this);
		break;

	case UNHIDE:
	//	pOp = new opUnhide(this);
		break;

	case MATCH_SHAPES:
		pOp = new opMatchShapes(this);
		break;

	case STATUS:
		break;

	default: 
		return NULL;
	}

	return pOp;
}



//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

void controller::UpdateInterface() const		//Draw all shapes on the user interface
{	
	pGraph->Draw(pGUI);
}


void controller::Save(ofstream& file) const		//Save all shapes on the user interface
{
	pGraph->Save(file);
}

void controller::Load(ifstream& file)			//Load all shapes to the user interface
{
	pGraph->Load(file,pGUI);
}



//==================================================================================//
//									get pointers									//
//==================================================================================//
GUI *controller::GetUI() const			//Return a pointer to the UI
{	return pGUI;}

Graph* controller::getGraph() const		//Return a pointer to the Graph
{	return pGraph;}



//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run()
{
	operationType OpType;
	do
	{
		OpType = GetUseroperation();					//1. Ask the GUI to read the required operation from the user

		operation* pOpr = createOperation(OpType);		//2. Create an operation coresspondingly
		 
		if (pOpr) {										//3. Execute the created operation
			pOpr->Execute();
			if (dynamic_cast<opExit*> (pOpr))
			{
				break;
			}
			delete pOpr;
			pOpr = nullptr;
		}
		
		UpdateInterface();								//4. Update the interface

	} while (OpType != EXIT);

}



//==================================================================================//
//									Detructor										//
//==================================================================================//
controller::~controller()
{
	delete pGUI; delete pGraph;
}
