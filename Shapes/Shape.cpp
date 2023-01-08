#include "shape.h"

shape::shape() {
	ShpGfxInfo.BorderWdth = 0;		 ShpGfxInfo.DrawClr = BLUE;
	ShpGfxInfo.FillClr = BLUE;		 ShpGfxInfo.image = "Empty";
	ShpGfxInfo.isFilled = false;	 ShpGfxInfo.isSelected = false;
	resizing = false;
}

shape::shape(GfxInfo shapeGfxInfo) {
	ID_gen++;
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
	resizing = false;
}
 
int shape::ID_gen = 0;

void shape::set_resizing(bool x)
{
	resizing = x;
}

int shape::get_crnt_id()
{
	return ID;
}

bool shape::check_id(shape* temp)
{
	if (this->ID == temp->ID)
	{
		return true;
	}
	else
		return
			false;
}

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


void shape::scale_two_points(Point& main, Point& second, double scale)
{
	double dist = sqrt(pow(main.x - second.x, 2) + pow(main.y - second.y, 2));
	double new_dist = dist * scale;
	double ratio = new_dist / dist;
	second.x = ((1 - ratio) * main.x + ratio * second.x);
	second.y = ((1 - ratio) * main.y + ratio * second.y);
}

double shape::calc_area_of_triangle(Point p1, Point p2, Point p3)
{
	double area = abs((p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x) / 2.0);
	return area;
}

bool shape::is_point_inside_rect(Point rect_c1, Point rect_c2, Point temp)
{
	Point Corner1 = rect_c1;

	Point Corner2 = rect_c2;

	Point Corner3;
	Corner3.x = Corner2.x;
	Corner3.y = Corner1.y;

	Point Corner4;
	Corner4.x = Corner1.x;
	Corner4.y = Corner2.y;

	double tri_1 = calc_area_of_triangle(Corner1, Corner3, temp);
	double tri_2 = calc_area_of_triangle(Corner3, Corner2, temp);
	double tri_3 = calc_area_of_triangle(Corner2, Corner4, temp);
	double tri_4 = calc_area_of_triangle(Corner4, Corner1, temp);
	double area_of_rect = abs(Corner1.x - Corner2.x) * abs(Corner1.y - Corner2.y);

	if (area_of_rect == tri_1 + tri_2 + tri_3 + tri_4)
	{
		return true;
	}
	else
		return false;
}
