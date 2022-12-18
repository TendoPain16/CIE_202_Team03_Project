#pragma once
#include "..\defs.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <vector>


//Base class for all shapes
class shape
{
protected:
	int ID;					//Each shape has an ID
	GfxInfo ShpGfxInfo;		//shape graphis info
	static int ID_gen;		//static id with all shape


public:
	shape();
	shape(GfxInfo shapeGfxInfo);
	virtual ~shape() {}

	void SetSelected(bool s);								//select/unselect the shape
	bool IsSelected() const;								//check whether fig is selected
	void ChngDrawClr(color Dclr);							//changes the shape's drawing color
	void ChngFillClr(color Fclr);							//changes the shape's filling color
	static int Get_ID();									//get current static id 

	virtual void Draw(GUI* pUI) const = 0;					//Draw the shape
	virtual void Save(ofstream& file) const = 0;			//Save the shape parameters to the file
	virtual void Load(vector <string> line, GUI* pUI) = 0;	//Load the shape parameters to the file
	//virtual void Rotate() = 0;							//Rotate the shape
	//virtual void Resize() = 0;							//Resize the shape
	//virtual void Move() = 0;								//Move the shape
	//virtual void PrintInfo(Output* pOut) = 0;				//print all shape info on the status bar
	

};

