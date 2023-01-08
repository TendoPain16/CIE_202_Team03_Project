#pragma once



#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"
#include <vector>
#include <string>
using namespace std;

struct Point	//To be used for shapes points
{
	int x, y;
};



struct action
{
protected:
	keytype key = NO_KEYPRESS;
	clicktype click = NO_CLICK;
	char character_clicked = ' ';
	Point point_clicked;
	
public:
	void set_members(keytype key,clicktype click,char character,Point point)
	{
		this->key = key;
		this->click = click;
		this->character_clicked = character;
		this->point_clicked.x = point.x;
		this->point_clicked.y = point.y;
	}
	clicktype get_mouse_click()
	{
		switch (click)
		{
		case NO_CLICK: return NO_CLICK; break;
		case LEFT_CLICK: return LEFT_CLICK; break;
		case RIGHT_CLICK: return RIGHT_CLICK; break;
		default: return NO_CLICK;
		}
	}

	char get_key_pressed()
	{
		if (key == ASCII)
		{
			return character_clicked;
		}
	}
	Point Get_Point()
	{
		return point_clicked;
	}


};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr;	//Draw color of the shape
	color FillClr;	//Fill color of the shape
	bool isFilled;	//shape Filled or not
	int BorderWdth;	//Width of shape borders
	bool isSelected;	//true if the shape is selected.
	string image;
};

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuIcon //The icons of the Draw menu (you should add more icons)
{
	//Note: Icons are ordered here as they appear in menu
	//If you want to change the menu icons order, change the order here
	ICON_RECT,		//Recangle icon in menu
	ICON_CIRC,		//Circle icon in menu
	ICON_SQUA,
	ICON_TRIA,
	ICON_IRREGPOL,
	ICON_LINE,
	ICON_DRAW_CLR,
	ICON_FILL_CLR,
	ICON_DEL,
	ICON_RESIZE,
	ICON_GROUP_SHAPES,
	ICON_UNGROUP_SHAPES,
	ICON_SAVE,
	ICON_LOAD,
	ICON_TO_PLAY,
	//TODO: Add more icons names here

	ICON_EXIT,		//Exit icon

	DRAW_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

};

enum PlayMenuIcon //The icons of the Play menu (you should add more icons)
{
	ICON_PLAY,
	ICON_RESTART,
	ICON_HIDE,
	ICON_UNHIDE,
	ICON_TO_DRAW,
	ICON_PEXIT,

	PLAY_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

};


class GUI
{



	GUI_MODE InterfaceMode;
	action temp;
	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuIconWidth;		//Width of each icon in toolbar menu


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed



	window* pWind;

public:

	GUI();



	
	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreatePlayToolBar();	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	// -- shapes Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const;  //Draw a rectangle
	void DrawCircle(Point P1, Point P2, GfxInfo CircGfxInfo) const;  //Draw a circle
	void DrawSquare(Point P1, Point P2, GfxInfo SquaGfxInfo) const;  //Draw a square
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo) const;  //Draw a line
	void DrawTriangle(Point P1, Point P2,Point P3, GfxInfo TriaGfxInfo) const;  //Draw a triangle
	void DrawIrregularpolygon(vector <Point> Points, int V_number, GfxInfo IrregpolGfxInfo) const;  //Draw a irregularpolygon
	void DrawSquareInPoint(Point temp);
	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg) const;	//Print a message on Status bar


	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	operationType GetUseroperation(); //Read the user click and map to an operation
	string GetSrting(string type) const;	 //Returns a string entered by the user
	color getCrntDrawColor() const;		//get current drwawing color
	color getCrntFillColor() const;		//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	void Get_action();

	void draw_string(int x, int y, string temp);
	GUI_MODE get_current_mode();
	void SetCrntMode(GUI_MODE x);		//set current mode
	void SetCrntDrawColor(color x);		//set current draw color
	void SerCrntfillColor(color x);
	action Get_current_action_info() const;
	buttonstate get_mouse_state(int& x, int& y);
	keytype get_key(char& x);
	color GetColor() const;
	void flushQueue();
	void set_Buffering(bool x);
	void update_buffer();
	void create_bar();

	~GUI();
};

