#include "GUI.h"

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

string GUI::GetSrting(string type) const
{
	string Label = "";
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		if (type == "name")
			PrintMessage("Please Enter the name: " + Label);
		else
			PrintMessage("Please Enter the number: " + Label);

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
operationType GUI::GetUseroperation() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / MenuIconWidth);
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case ICON_RECT:					return DRAW_RECT;
			case ICON_CIRC:					return DRAW_CIRC;
			case 2/*ICON_SQUA*/:			return DRAW_SQUA;
			case 3/*ICON_TRIA*/:			return DRAW_TRIA;
			case 4/*ICON_IRREGPOL*/:		return DRAW_IRREGPOL;
			case 5/*ICON_LINE*/:			return DRAW_LINE;
			case 6/*ICON_DRAW_CLR*/:		return CHNG_DRAW_CLR;
			case 7/*ICON_FILL_CLR*/:		return CHNG_FILL_CLR;
			case 8/*ICON_DEL*/:				return DEL;
			case 9/*ICON_RESIZE*/:			return RESIZE;
			case 10/*ICON*/:				return EMPTY;
			case 11/*ICON*/:				return EMPTY;
			case 12/*ICON*/:				return EMPTY;
			case 13/*ICON*/:				return EMPTY;
			case 14/*ICON*/:				return EMPTY;
			case 15/*ICON*/:				return EMPTY;
			case 16/*ICON*/:				return SAVE;
			case 17/*ICON_LOAD*/:			return LOAD;
			case 18/*ICON_TO_PLAY*/:		return TO_PLAY;
			case 19/*ICON_EXIT*/:			return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < ToolBarHeight)
		{
			//Check whick Menu icon was clicked
			//==> This assumes that menu icons are lined up horizontally <==
			int ClickedIconOrder = (x / MenuIconWidth);
			//Divide x coord of the point clicked by the menu icon width (int division)
			//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

			switch (ClickedIconOrder)
			{
			case 0/*ICON*/:				return EMPTY;
			case 1/*ICON*/:				return EMPTY;
			case 2/*ICON*/:				return EMPTY;
			case 3/*ICON*/:				return EMPTY;
			case 4/*ICON*/:				return EMPTY;
			case 5/*ICON*/:				return EMPTY;
			case 6/*ICON*/:				return EMPTY;
			case 7/*ICON*/:				return EMPTY;
			case 8/*ICON*/:				return EMPTY;
			case 9/*ICON*/:				return EMPTY;
			case 10/*ICON*/:			return EMPTY;
			case 11/*ICON*/:			return EMPTY;
			case 12/*ICON*/:			return EMPTY;
			case 13/*ICON*/:			return EMPTY;
			case 14/*ICON*/:			return EMPTY;
			case 15/*ICON*/:			return EMPTY;
			case 16/*ICON*/:			return EMPTY;
			case 17/*ICON*/:			return EMPTY;
			case 18/*ICON*/:			return EMPTY;
			case 19/*ICON*/:			return EMPTY;

			default: return EMPTY; 	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the playing area
		if (y >= ToolBarHeight && y < height - StatusBarHeight)
		{
			return PLAYING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
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
	MenuIconImages[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_CIRC] = "images\\MenuIcons\\Menu_Circ.jpg";
	MenuIconImages[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu icon and add it to the list

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
	///TODO: write code to create Play mode menu
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
	x->~window();
	return y;
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

GUI_MODE GUI::GetCrntMode() const
{
	return InterfaceMode;
}

void GUI::SetCrntMode(GUI_MODE x)
{
	InterfaceMode = x;
}

void GUI::SetCrntDrawColor(color x)
{
	DrawColor = x;
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

void GUI::DrawCircle(Point P1, Point P2, GfxInfo RectGfxInfo) const
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

	pWind->DrawCircle(P1.x, P1.y, sqrt(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2)), style);

}

void GUI::DrawSquare(Point P1, Point P2, GfxInfo RectGfxInfo) const
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

	pWind->DrawRectangle(P1.x, P1.y, P1.x + (P2.x - P1.x), P1.y + (P2.x - P1.x), style);

}

void GUI::DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo) const
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

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

