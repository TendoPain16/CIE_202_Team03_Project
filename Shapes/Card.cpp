#include "Card.h"


Card::Card()
{
	pic = NULL;
	Corner1.x = 0; Corner1.y = 0;
	Corner2.x = 0; Corner2.y = 0;
	Card_Center.x = 0; Card_Center.y = 0;
	Card_Info.BorderWdth = 1;
	Card_Info.DrawClr = BLUE;
	Card_Info.FillClr = BLUE;
	Card_Info.isFilled = false;
	Card_Info.isSelected = false;
}

Card::Card(shape* shp,Point Center)
{
	Card_Center = Center;
	pic = shp;
	pic->save_shape_points();
	pic->move_to_center(Card_Center);
	Corner1.x = Card_Center.x - 39;
	Corner1.y = Card_Center.y - 50;
	Corner2.x = Card_Center.x + 39;
	Corner2.y = Card_Center.y + 50;
	while (pic->is_shape_between_two_corners(Corner1,Corner2) == false)
	{
		pic->Resize(0.75);
	}
	Card_Info.BorderWdth = 1;
	Card_Info.DrawClr = BLUE;
	Card_Info.FillClr = BLUE;
	Card_Info.isFilled = true;
	Card_Info.isSelected = true;
}

Card::~Card()
{
	pic->load_shape_points();
}


bool Card::is_covered()
{
	return Card_Info.isFilled;
}

void Card::set_covered(bool x)
{
	Card_Info.isFilled = x;
}

double Card::calc_area_of_triangle(Point p1, Point p2, Point p3)
{
	double area = abs((p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x) / 2.0);
	return area;
}

bool Card::IsPointInside(int x, int y)
{
	Point temp;
	temp.x = x;
	temp.y = y;

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

void Card::Draw(GUI* pUI)
{
	pic->Draw(pUI);
	pUI->DrawRect(Corner1, Corner2, Card_Info);

}

bool Card::check_card(Card* temp)
{
	if (this->pic->check_id(temp->pic))
	{
		return true;
	}
	else 
		return false;
}