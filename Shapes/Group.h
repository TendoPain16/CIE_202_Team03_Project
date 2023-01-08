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
	Group(Group* x);
	virtual ~Group();
	virtual void Draw(GUI* pUI) const;
	virtual void Save(ofstream&) const;
	virtual void Load(vector <string> line, GUI* pUI, ifstream* inputfile = nullptr);
	virtual void Resize(double number);
	virtual void Move(Point old_point, Point new_point);
	virtual int is_on_corners(Point x);
	virtual void Resize_By_Drag(int point_number, Point old_point, Point new_point);
	virtual bool IsPointInside(int x, int y);
	virtual void save_shape_points();
	virtual void load_shape_points();
	virtual bool is_shape_between_two_corners(Point p1, Point p2);
	virtual void move_to_center(Point new_center);

	virtual vector <shape*> get_shapes_list();
};
