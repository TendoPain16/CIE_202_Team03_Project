#include "shape.h"

shape::shape()
{
	GfxInfo temp;
	temp.BorderWdth = 0;
	temp.DrawClr = BLUE;
	temp.FillClr = BLUE;
	temp.image = "Empty";
	temp.isFilled = false;
	temp.isSelected = false;
	ShpGfxInfo = temp;
}

shape::shape(GfxInfo shapeGfxInfo)
{
	ID_gen++;
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}
 
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}

int shape::ID_gen = 0;

int shape::Get_ID()
{
	return ID_gen;
}
