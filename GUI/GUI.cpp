#include "GUI.h"
#include <iostream>
GUI::GUI()
{
	//Initialize user interface parameters
	InterfaceMode = MODE_DRAW;

	width = 1300;
	height = 700;
	wx = 5;
	wy = 5;


	StatusBarHeight = 50;
	ToolBarHeight = 50;
	MenuIconWidth = 65;

	DrawColor = BLUE;	//default Drawing color
	FillColor = GREEN;	//default Filling color
	MsgColor = BLACK;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use if for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames


	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - PAINT ^ ^ PLAY - - - - - - - - - -");

	CreateDrawToolBar();
	CreateStatusBar();
}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

void GUI::flushQueue()
{
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
}
void GUI::set_Buffering(bool x)
{
	pWind->SetBuffering(x);
}
buttonstate GUI::get_mouse_state(int& x, int& y)
{
	return (pWind->GetButtonState(LEFT_BUTTON,x, y));
}
keytype GUI::get_key(char& x)
{
	return pWind->GetKeyPress(x);
}

void GUI::draw_string(int x , int y ,string temp)
{
	pWind->DrawString(x, y, temp);
}

GUI_MODE GUI::get_current_mode()
{
	return InterfaceMode;
}

void GUI::update_buffer()
{
	pWind->UpdateBuffer();
}

void GUI::SerCrntfillColor(color x)
{
	FillColor = x;
}

string GUI::GetSrting(string message) const
{
	string Label = "";
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{

		PrintMessage(message + Label);

		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
		{
			PrintMessage("Cancelled");
			return "";	//returns nothing as user has cancelled label
		}
		if (Key == 13)	//ENTER key is pressed
		{
			PrintMessage("Done");
			return Label;
		}
		if (Key == 8)	//BackSpace is pressed
		{
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		}
		else
			Label += Key;

	}
}

//This function reads the position where the user clicks to determine the desired operation
void GUI::Get_action()
{
	char c;
	Point d;
	keytype key;
	clicktype click;

	bool bQuit = false;

	(*pWind).SetBuffering(true);
	// Flush out the input queues before beginning
	(*pWind).FlushMouseQueue();
	(*pWind).FlushKeyQueue();

	do
	{
		key = (*pWind).GetKeyPress(c);
		click = (*pWind).GetMouseClick(d.x, d.y);

		if (key == ESCAPE)
		{
			cout << "Escape is pressed." << endl;
		}
		else if (key == ASCII)
		{
			cout << "The ASCII key '" << c << "' was pressed." << endl;
		}
		else if (key == FUNCTION)
		{
			cout << "The Function key F" << int(c) << " was pressed." << endl;
		}

		else if (key == ARROW)
		{
			switch (c)
			{
			case 1:
				cout << "The End key was pressed." << endl;
				break;
			case 2:
				cout << "The Down Arrow key was pressed." << endl;
				break;
			case 3:
				cout << "The Page Down key was pressed." << endl;
				break;
			case 4:
				cout << "The Left Arrow key was pressed." << endl;
				break;
			case 5:
				cout << "The Center Keypad key was pressed." << endl;
				break;
			case 6:
				cout << "The Right Arrow key was pressed." << endl;
				break;
			case 7:
				cout << "The Home key was pressed." << endl;
				break;
			case 8:
				cout << "The Up Arrow key was pressed." << endl;
				break;
			case 9:
				cout << "The Page Up key was pressed." << endl;
			}
		}


		if (click == LEFT_CLICK)
		{
			cout << "The mouse was left-clicked at (" << d.x << ", " << d.y << ")." << endl;
		}
		else if (click == RIGHT_CLICK)
		{
			cout << "The mouse was right-clicked at (" << d.x << ", " << d.y << ")." << endl;
		}
	} while ((click == 0) && (key == 0));

	(*pWind).SetBuffering(false);
	temp.set_members(key, click, c, d);

}

operationType GUI::GetUseroperation()
{
	Get_action();

	if (InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		if (temp.Get_Point().y >= 0 && temp.Get_Point().y < ToolBarHeight) //tool bar
		{
			if (temp.get_mouse_click() == LEFT_CLICK) // left click
			{
				int ClickedIconOrder = (temp.Get_Point().x / MenuIconWidth);

				switch (ClickedIconOrder)
				{
				case ICON_RECT:				return DRAW_RECT;
				case ICON_CIRC:				return DRAW_CIRC;
				case ICON_SQUA:				return DRAW_SQUA;
				case ICON_TRIA:				return DRAW_TRIA;
				case ICON_IRREGPOL:			return DRAW_IRREGPOL;
				case ICON_LINE:				return DRAW_LINE;
				case ICON_DRAW_CLR:			return CHNG_DRAW_CLR;
				case ICON_FILL_CLR:			return CHNG_FILL_CLR;
				case ICON_DEL:				return DEL;
				case ICON_RESIZE:			return RESIZE;
				case ICON_GROUP_SHAPES:		return GROUP_SHAPES;
				case ICON_UNGROUP_SHAPES:	return UN_GROUP_SHAPES;
				case ICON_SAVE:				return SAVE;
				case ICON_LOAD:				return LOAD;
				case ICON_TO_PLAY:			return TO_PLAY;
				case ICON_EXIT:				return EXIT;
				default: return EMPTY;
				}
			}
		}

		else if (temp.Get_Point().y >= ToolBarHeight && temp.Get_Point().y < height - StatusBarHeight) //drawing area
		{
			if ((temp.get_mouse_click() == LEFT_CLICK) || (temp.get_mouse_click() == RIGHT_CLICK)) //left or right click
			{
				return SELECT;
			}
		}
		else if ((temp.get_key_pressed() == 'm') || (temp.get_key_pressed() == 'M')) //move
		{
			return MOVE;
		}
		else if ((temp.get_key_pressed() == 'r') || (temp.get_key_pressed() == 'R')) //resize by drag
		{
			return RESIZE_BY_DRAG;
		}
		else if ((temp.get_key_pressed() == 'd') || (temp.get_key_pressed() == 'D')) //resize by drag
		{
			return DUPLICAT;
		}
		else if ((temp.get_key_pressed() == 's') || (temp.get_key_pressed() == 'S')) //resize by drag
		{
			return SCRAMBLE;
		}
		else if ((temp.get_key_pressed() == 3)) //copy
		{
			return COPY;
		}
		else if ((temp.get_key_pressed() == 22)) //paste
		{
			return PASTE;
		}
		return STATUS;
	}

	else	//GUI is in PLAY mode
	{
		if (temp.Get_Point().y >= 0 && temp.Get_Point().y < ToolBarHeight) //tool bar
		{
			if (temp.get_mouse_click() == LEFT_CLICK) // left click
			{
				int ClickedIconOrder = (temp.Get_Point().x / MenuIconWidth);

				switch (ClickedIconOrder)
				{
				case ICON_PLAY:				return START_GAME;
				case ICON_RESTART:			return RESTART_GAME;
				case ICON_HIDE:				return HIDE;
				case ICON_UNHIDE:			return UNHIDE;
				case ICON_TO_DRAW:			return TO_DRAW;
				case ICON_PEXIT:				return EXIT;
				default: return EMPTY;
				}
			}
		}

		else if (temp.Get_Point().y >= ToolBarHeight && temp.Get_Point().y < height - StatusBarHeight) //playing area
		{
			if (temp.get_mouse_click() == LEFT_CLICK) // left click
			{
				return MATCH_SHAPES;
			}
		}
		return STATUS;	//[3] User clicks on the status bar
	}

}
////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() 
{
	InterfaceMode = MODE_DRAW;
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	//First prepare List of images for each menu icon
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuIcon
	string MenuIconImages[DRAW_ICON_COUNT];
	MenuIconImages[ICON_RECT]			= "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_CIRC]			= "images\\MenuIcons\\Menu_Circ.jpg";
	MenuIconImages[ICON_SQUA]			= "images\\MenuIcons\\Menu_Square.jpg";
	MenuIconImages[ICON_TRIA]			= "images\\MenuIcons\\Menu_Triangle.jpg";
	MenuIconImages[ICON_IRREGPOL]		= "images\\MenuIcons\\Menu_IrregularPolygon.jpg";
	MenuIconImages[ICON_LINE]			= "images\\MenuIcons\\Menu_Line.jpg";
	MenuIconImages[ICON_DRAW_CLR]		= "images\\MenuIcons\\Menu_Pen.jpg";
	MenuIconImages[ICON_FILL_CLR]		= "images\\MenuIcons\\Menu_Fill.jpg";
	MenuIconImages[ICON_DEL]			= "images\\MenuIcons\\Menu_Delete.jpg";
	MenuIconImages[ICON_RESIZE]			= "images\\MenuIcons\\Menu_Resize.jpg";
	MenuIconImages[ICON_GROUP_SHAPES]   = "images\\MenuIcons\\Menu_Group.jpg";
	MenuIconImages[ICON_UNGROUP_SHAPES] = "images\\MenuIcons\\Menu_UnGroup.jpg";
	MenuIconImages[ICON_SAVE]			= "images\\MenuIcons\\Menu_Save.jpg";
	MenuIconImages[ICON_LOAD]			= "images\\MenuIcons\\Menu_Load.jpg";
	MenuIconImages[ICON_TO_PLAY]		= "images\\MenuIcons\\Menu_Play.jpg";
	MenuIconImages[ICON_EXIT]			= "images\\MenuIcons\\Menu_Exit.jpg";
	//TODO: Prepare images for each menu icon and add it to the list
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(0, 0, pWind->GetWidth(), ToolBarHeight);
	//Draw menu icon one image at a time
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() 
{
	InterfaceMode = MODE_PLAY;


	string MenuIconImages[PLAY_ICON_COUNT];
	MenuIconImages[ICON_PLAY] = "images\\MenuIcons\\Menu_Play.jpg";
	MenuIconImages[ICON_RESTART] = "images\\MenuIcons\\Menu_Restart.jpg";
	MenuIconImages[ICON_HIDE] = "images\\MenuIcons\\Menu_Hide.jpg";
	MenuIconImages[ICON_UNHIDE] = "images\\MenuIcons\\Menu_Unhide.jpg";
	MenuIconImages[ICON_TO_DRAW] = "images\\MenuIcons\\Menu_Pen.jpg";
	MenuIconImages[ICON_PEXIT] = "images\\MenuIcons\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu icon and add it to the list
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(0, 0, pWind->GetWidth(), ToolBarHeight);
	//Draw menu icon one image at a time
	for (int i = 0; i < PLAY_ICON_COUNT; i++)
		pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);	
}
//////////////////////////////////////////////////////////////////////////////////////////
color GUI::GetColor() const
{
	window* x = CreateWind(400, 400, width / 4, height / 4);

	string image = "images\\MenuIcons\\Colors.jpg";
	x->DrawImage(image, 0, 0, 400, 400);

	Point temp;
	x->WaitMouseClick(temp.x, temp.y);

	color y = x->GetColor(temp.x, temp.y);
	delete x;
	return y;
}


void GUI::create_bar()
{
	if (InterfaceMode == MODE_DRAW)
	{
		CreateDrawToolBar();
	}
	else
	{
		CreatePlayToolBar();
	}
}
/// /////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}

void GUI::SetCrntMode(GUI_MODE x)
{
	InterfaceMode = x;
}

void GUI::SetCrntDrawColor(color x)
{
	DrawColor = x;
}


action GUI::Get_current_action_info() const
{
	return temp;
}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;
	if (RectGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}

void GUI::DrawCircle(Point P1, Point P2, GfxInfo CircGfxInfo) const
{
	color DrawingClr;
	if (CircGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = CircGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (CircGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawCircle(P1.x, P1.y, sqrt(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2)), style);

}

void GUI::DrawSquare(Point P1, Point P2, GfxInfo SquaGfxInfo) const
{
	color DrawingClr;
	if (SquaGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = SquaGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, SquaGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (SquaGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquaGfxInfo.FillClr);
	}
	else
		style = FRAME;
	

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}

void GUI::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo) const
{
	color DrawingClr;
	if (LineGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (LineGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(LineGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}

void GUI::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriaGfxInfo) const
{
	color DrawingClr;
	if (TriaGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = TriaGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriaGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriaGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriaGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y,P3.x,P3.y, style);

}

//const int* ipX, const int* ipY, const int iVertices, const drawstyle dsStyle
void GUI::DrawIrregularpolygon(vector <Point> Points,int V_number, GfxInfo IrregpolGfxInfo) const
{
	color DrawingClr;
	if (IrregpolGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = IrregpolGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, IrregpolGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (IrregpolGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(IrregpolGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int* x = new int[V_number];
	int* y = new int[V_number];
	for (int i = 0; i < V_number; i++)
	{
		x[i] = Points[i].x;
		y[i] = Points[i].y;
	}

	pWind->DrawPolygon(x,y , V_number, style);

}

void GUI::DrawSquareInPoint(Point temp)
{
	pWind->SetPen(ORANGE, 1);	//Set Drawing color & width
	pWind->SetBrush(ORANGE);


	Point p1;
	Point p2;
	p1.x = temp.x - 5;
	p1.y = temp.y - 5;
	p2.x = temp.x + 5;
	p2.y = temp.y + 5;
	pWind->DrawRectangle(p1.x, p1.y, p2.x, p2.y, FILLED);
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

