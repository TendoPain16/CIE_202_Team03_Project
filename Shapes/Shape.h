#pragma once
#include "..\defs.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <vector>


struct gfxinfo_change_Counter
{
	int dclr = 0;
	int fclr = 0;
	int bw = 0;
	int issel = 0;
	int isfill = 0;
};

//Base class for all shapes
class shape
{
protected:
	int ID;					//Each shape has an ID
	GfxInfo ShpGfxInfo;		//shape graphis info
	static int ID_gen;		//static id with all shape
	gfxinfo_change_Counter counter;
	bool resizing;
	vector<Point> shape_points;

public:
	
	shape();
	shape(GfxInfo shapeGfxInfo);
	virtual ~shape() {}

	bool check_id(shape* temp);
	void set_resizing(bool x);
	void SetSelected(bool s);								//select/unselect the shape
	bool IsSelected() const;								//check whether fig is selected
	void ChngDrawClr(color Dclr);							//changes the shape's drawing color
	void ChngFillClr(color Fclr);							//changes the shape's filling color
	bool IsFilled() const;								//check whether fig is selected
	void SetFilled(bool s);
	void ChngBorderWidth(int w);
	static int Get_ID();									//get current static id 
	virtual void Draw(GUI* pUI) const = 0;					//Draw the shape
	virtual void Save(ofstream& file) const = 0;			//Save the shape parameters to the file
	virtual void Load(vector <string> line, GUI* pUI, ifstream* inputfile = nullptr) = 0;	//Load the shape parameters to the file
	virtual void Move(Point old_point,Point new_point) = 0;	//Move the shape
	virtual void Resize(double number) = 0;					//Resize the shape
	virtual bool IsPointInside(int x,int y) = 0;
	//virtual void PrintInfo(Output* pOut) = 0;				//print all shape info on the status bar
	//virtual void Rotate() = 0;							//Rotate the shape
	double calc_area_of_triangle(Point p1, Point p2,Point p3);
	bool is_point_inside_rect(Point rect_c1, Point rect_c2, Point temp);
	virtual void save_shape_points() = 0;
	virtual void load_shape_points() = 0;
	virtual bool is_shape_between_two_corners(Point p1,Point p2) = 0;
	virtual void move_to_center(Point new_center) = 0;
	int get_crnt_id();
	void scale_two_points(Point& main, Point& second, double scale);
	virtual int is_on_corners(Point x) = 0;
	virtual void Resize_By_Drag(int point_number,Point old_point, Point new_point) = 0;			//Resize the shape by drag
	
};

