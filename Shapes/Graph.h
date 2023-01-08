#pragma once
#include "Shape.h"
#include "Card.h"
#include <fstream>
#include <vector>
using namespace std;


class GUI;	//forward decl


class Graph			//A class that is responsible on everything related to shapes
{
private:
	vector <shape*> shapesList;		 //a container to hold all shapes				
	shape* selectedShape;		  	 //pointer to the currently selected shape
	vector <shape*> play_shapes;
	vector<Card*> play_cards;

public:										
	Graph();
	~Graph();

	void Addshape(shape* pFig);					//Adds a new shape to the shapesList.
	void Addshapes(vector <shape*> pFigs);
	void Draw(GUI* pUI) const;					//Draw the graph (draw all shapes).
	void Clear_shapeslist();					//clear all shapes.
	void clear_cards();
	shape* Getshape(int x, int y) const;		//Search for a shape given a point inside the shape.


	void change_draw_clr(GUI* pUI, color temp);
	void Save(ofstream& outfile);				//Save all shapes to a file.
	void Load(ifstream& inputfile, GUI* pUI);	//Load all shapes from a file.
	void move_shapes(GUI* pUI);
	void resize(double number);
	void Resize_By_Drag(GUI* pUI);
	void group_shapes();
	void Dublicate();
	void Scramble();
	void Matsh_Shapes(GUI* pUI);
	void Scramble_shapes_in_play();
	void Start_Game();
	void Restart_Game();
	void ungroup_shapes();
	void select(action temp);
	vector <shape*> GetShapesList() const;
};
