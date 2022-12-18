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
{	ShpGfxInfo.isSelected = s; }


bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }


void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }


void shape::ChngFillClr(color Fclr)
{	 ShpGfxInfo.isFilled = true;	ShpGfxInfo.FillClr = Fclr; }

int shape::Get_ID()
{return ID_gen;}
