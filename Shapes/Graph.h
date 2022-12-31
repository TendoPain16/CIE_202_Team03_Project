#pragma once
#include "Shape.h"
#include <fstream>
#include <vector>
using namespace std;


class GUI;	//forward decl


class Graph			//A class that is responsible on everything related to shapes
{
private:
	vector <shape*> shapesList;		 //a container to hold all shapes				
	shape* selectedShape;		  	 //pointer to the currently selected shape

public:										
	Graph();
	~Graph();

	void Addshape(shape* pFig);					//Adds a new shape to the shapesList.
	void Draw(GUI* pUI) const;					//Draw the graph (draw all shapes).
	void Save(ofstream& outfile);				//Save all shapes to a file.
	void Load(ifstream& inputfile, GUI* pUI);	//Load all shapes from a file.
	void Clear_shapeslist();					//clear all shapes.
	void resize(double number);
	vector <shape*> group_shapes();
	shape* Getshape(int x, int y) const;		//Search for a shape given a point inside the shape.
	vector <shape*> GetShapesList() const;
	void SetShapesList(vector <shape*> x);
};
