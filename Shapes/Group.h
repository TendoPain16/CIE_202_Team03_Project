#pragma once
#include "shape.h" 
#include <fstream>

class Group : public shape
{
private:
	vector <shape*> groupshapesList;
	

public:
	Group();
	Group(vector <shape*> come, GfxInfo shapeGfxInfo);
	virtual ~Group();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream&) const;
	virtual void Load(vector <string> line, GUI* pUI, ifstream* inputfile = nullptr);
	virtual void Resize(double number);

	virtual vector <shape*> get_shapes_list();
};
