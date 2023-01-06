#pragma once

#include "DEFS.h"
#include "Shapes\Graph.h"
#include "GUI\GUI.h"

class operation; //forward declaration

//Main class that manages everything in the application.
class controller
{

	Graph* pGraph;								//pointe to the grapg
	GUI* pGUI;									//Pointer to UI class
	

public:	
	controller(); 
	~controller();
	
	// -- operation-Related Functions
	operationType GetUseroperation();		//Reads the input command from the user and returns the corresponding operation type
	operation* createOperation(operationType) ; //Creates an operation
	void Run();
	
	
	
	// -- Interface Management Functions
	Graph* getGraph() const;					//Return pointer to the graph
	GUI *GetUI() const;							//Return pointer to the UI
	void UpdateInterface() const;				//Redraws all the drawing window	
	void Save(ofstream&) const;					//Save all shapes on the user interface
	void Load(ifstream&);						//Load all shapes to the user interface

};

