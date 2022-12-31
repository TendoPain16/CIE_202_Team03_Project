#include "shape.h"

shape::shape() {
	ShpGfxInfo.BorderWdth = 0;		 ShpGfxInfo.DrawClr = BLUE;
	ShpGfxInfo.FillClr = BLUE;		 ShpGfxInfo.image = "Empty";
	ShpGfxInfo.isFilled = false;	 ShpGfxInfo.isSelected = false;
}

shape::shape(GfxInfo shapeGfxInfo) {
	ID_gen++;
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}
 
int shape::ID_gen = 0;


void shape::SetSelected(bool s)
{
	ShpGfxInfo.isSelected = s;
	counter.issel++;
}


bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

bool shape::IsFilled() const
{	return ShpGfxInfo.isFilled; }



void shape::ChngDrawClr(color Dclr)
{
	ShpGfxInfo.DrawClr = Dclr;
	counter.dclr++;
}


void shape::ChngFillClr(color Fclr)
{	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
	counter.fclr++;
	counter.isfill++;
}

void shape::SetFilled(bool s)
{
	ShpGfxInfo.isFilled = s; 
	counter.isfill++;
}

void shape::ChngBorderWidth(int w)
{
	ShpGfxInfo.BorderWdth = w; 
	counter.bw++;
}

int shape::Get_ID()
{return ID_gen;}

int shape::Get_current_ID()
{return ID;}

void shape::scale_two_points(Point& main, Point& second, double scale)
{
	double dist = sqrt(pow(main.x - second.x, 2) + pow(main.y - second.y, 2));
	double new_dist = dist * scale;
	double ratio = new_dist / dist;
	second.x = ((1 - ratio) * main.x + ratio * second.x);
	second.y = ((1 - ratio) * main.y + ratio * second.y);
}