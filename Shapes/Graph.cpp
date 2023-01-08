#include <sstream>

#include "Graph.h"
#include "..\GUI\GUI.h"

#include "..\shapes\Square.h"
#include "..\shapes\Circle.h"
#include "..\shapes\Rect.h"
#include "..\Shapes\Triangle.h"
#include "..\shapes\Line.h"
#include "..\shapes\IrregularPolygon.h"
#include "..\shapes\RegularPolygon.h"
#include "..\shapes\Group.h"
#include <iostream>

Graph::Graph() {}

Graph::~Graph() {}



//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//
void Graph::Addshape(shape* pShp)	//Add a shape to the list of shapes
{
	shapesList.push_back(pShp);		//Add a new shape to the shapes vector
}

void Graph::Addshapes(vector <shape*> pFigs)
{
	for (int i = 0; i < pFigs.size(); i++)
	{
		shapesList.push_back(pFigs[i]);
	}
}


void Graph::Draw(GUI* pUI) const	//Draw all shapes on the user interface
{
	pUI->ClearDrawArea();
	if (pUI->get_current_mode() == MODE_DRAW)
	{
		for (auto shapePointer : shapesList)
			shapePointer->Draw(pUI);
	}
	else
	{
		for (auto card : play_cards)
		{
			card->Draw(pUI);
		}
	}
	pUI->create_bar();
}


shape* Graph::Getshape(int x, int y) const
{
	for (int i = shapesList.size() - 1; i >= 0; i--)
	{
		if (shapesList[i]->IsPointInside(x,y))
		{
			return shapesList[i];
		}		
	}
	return nullptr;
}


void Graph::Clear_shapeslist()
{
	for (int i = 0; i < shapesList.size(); i++)
	{
		delete shapesList[i];
	}
	shapesList.clear();
}


void Graph::Save(ofstream& outfile) 
{	
	for (auto shapePointer : shapesList)
		shapePointer->Save(outfile);
}


void Graph::Load(ifstream& inputfile, GUI* pUI)
{
	pUI->ClearDrawArea();
	shapesList.clear();

	
	vector <string> wordsList;
	string var;

	string line;
	while (getline(inputfile, line))
	{
		istringstream ss(line);
		wordsList.clear();
		while (ss >> var)
		{
			wordsList.push_back(var);
		}

		shape* R;
		switch (stoi(wordsList[0]))
		{
		case 0: R = new Rect(); break;
		case 1: R = new Square(); break;
		case 2: R = new Circle(); break;
		case 3: R = new Line(); break;
		case 4: R = new Triangle(); break;
		case 5: R = new IrregularPolygon(); break;
		case 6: R = new Group(); break;
		default: return;
		}

		R->Load(wordsList, pUI, &inputfile);
		
		Addshape(R);
	}
}


void Graph::resize(double number)
{
	for (auto shapePointer : shapesList)
	{
		if (shapePointer->IsSelected())
		{
			shapePointer->Resize(number);

			for (int i = 0; i < shapesList.size(); i++)
			{
				if ((shapePointer != shapesList[i]) && (shapePointer->check_id(shapesList[i])))
				{
					shapesList[i]->Resize(number);
				}
			}
		}
	}
}

void Graph::group_shapes()
{
	vector <shape*> ListOfShapes;
	vector <int> ShapesToBeDeleted;
	for (int i = 0; i < shapesList.size(); i++)
		if (shapesList[i]->IsSelected())
		{
			ListOfShapes.push_back(shapesList[i]);
			ShapesToBeDeleted.push_back(i);
		}

	for (auto x : ShapesToBeDeleted)
	{
		shapesList.erase(shapesList.begin() + x);
		for (int i = 0; i < ShapesToBeDeleted.size(); i++)
		{
			ShapesToBeDeleted[i] = ShapesToBeDeleted[i] - 1;
		}
	}



	if (ListOfShapes.size() != 0)
	{
		GfxInfo RectGfxInfo;
		RectGfxInfo.DrawClr;
		RectGfxInfo.FillClr;
		RectGfxInfo.BorderWdth;
		RectGfxInfo.image;
		RectGfxInfo.isFilled;
		RectGfxInfo.isSelected;

		Group* R = new Group(ListOfShapes, RectGfxInfo);
		Addshape(R);
	}
}

void Graph::ungroup_shapes()
{
	int num = shapesList.size();
	vector<int> groups_to_be_deleted;

	for (int i = 0; i < num; i++)
	{
		Group* current = dynamic_cast<Group*> (shapesList[i]);
		if ((current != NULL) && (shapesList[i]->IsSelected() == true))
		{

			vector <shape*> Group_shapes = current->get_shapes_list();
			for (int i = 0; i < Group_shapes.size(); i++)
			{
				Group_shapes[i]->SetSelected(false);
				shapesList.push_back(Group_shapes[i]);
			}
			for (int x = Group_shapes.size() - 1; x >= 0; x--)
			{
				Group_shapes.pop_back();
			}

			delete shapesList[i];
		}
	}

	for (int i = 0; i < groups_to_be_deleted.size(); i++)
	{
		shapesList.erase(shapesList.begin() + groups_to_be_deleted[i]);
		for (int x = i + i; x < groups_to_be_deleted.size(); x++)
		{
			groups_to_be_deleted[i] = groups_to_be_deleted[i] - 1;
		}
	}
}


void Graph::move_shapes(GUI* pUI)
{
	if (shapesList.size() == 0)
	{
		pUI->PrintMessage("no shape found");
		return;
	}

	// Flush out the input queues before beginning
	pUI->flushQueue();
	pUI->set_Buffering(true);

	bool bDragging = false;
	Point mouse_location;
	Point old_mouse_location;
	char cKeyData;
	bool selected = false;
	int x = -1;
	// Loop until there escape is pressed
	while (pUI->get_key(cKeyData) != ESCAPE)
	{
		//draw the page instead of the shapes and tool bar
		Draw(pUI);


		// Dragging voodoo
		
		if (bDragging == false)
		{
			if (pUI->get_mouse_state(mouse_location.x, mouse_location.y) == BUTTON_DOWN) //if mouse is clicked
			{
				for (int i = shapesList.size() - 1; i >= 0; i--)
				{
					if (shapesList[i]->IsPointInside(mouse_location.x,mouse_location.y))
					{
						bDragging = true;
						selected = shapesList[i]->IsSelected();
						old_mouse_location.x = mouse_location.x;
						old_mouse_location.y = mouse_location.y;
						x = i;
						break;
					}
				}
			}
		}


		else
		{
			if (pUI->get_mouse_state(mouse_location.x, mouse_location.y) == BUTTON_UP)
			{
				bDragging = false;
				x = -1;
			}
			else
			{
				if ((mouse_location.x != old_mouse_location.x) && (mouse_location.y != old_mouse_location.x))
				{
					if (x != -1)
					{
						if (selected == true)
						{
							for (int j = 0; j < shapesList.size(); j++)
							{
								if (shapesList[j]->IsSelected())
								{

									shapesList[j]->Move(old_mouse_location, mouse_location);
								}
							}
							old_mouse_location.x = mouse_location.x;
							old_mouse_location.y = mouse_location.y;
						}
						else
						{
							shapesList[x]->Move(old_mouse_location,mouse_location);
							old_mouse_location.x = mouse_location.x;
							old_mouse_location.y = mouse_location.y;
						}
					}
				}
			}
		}

		// Update the screen buffer
		pUI->update_buffer();
		pUI->PrintMessage("move is on");
	}
	pUI->PrintMessage("move is off");
	pUI->set_Buffering(false);

}

void Graph::Resize_By_Drag(GUI* pUI)
{
	// Flush out the input queues before beginning
	pUI->flushQueue();
	pUI->set_Buffering(true);

	int stat = 0;
	bool bDragging = false;
	Point mouse_location;
	Point old_mouse_location;
	Point first_click;
	char cKeyData;
	int x = 0;
	int num = 0;

	for (int i = 0; i < shapesList.size(); i++)
	{
		shapesList[i]->set_resizing(true);
	}

	// Loop until there escape is pressed
	while (pUI->get_key(cKeyData) != ESCAPE)
	{
		//draw the page instead of the shapes and tool bar
		Draw(pUI);


		// Dragging voodoo
		if (bDragging == false)
		{
			if (pUI->get_mouse_state(mouse_location.x, mouse_location.y) == BUTTON_DOWN) //if mouse is clicked
			{
				for (size_t i = 0; i < shapesList.size(); i++)
				{
					int number = shapesList[i]->is_on_corners(mouse_location);
					if (number != 0)
					{
						num = number;
						bDragging = true;
						x = i;
						old_mouse_location.x = mouse_location.x;
						old_mouse_location.y = mouse_location.y;
						shapesList[i]->Resize_By_Drag(number, old_mouse_location, mouse_location);
						break;
					}
				}
			}
		}


		else
		{
			if (pUI->get_mouse_state(mouse_location.x, mouse_location.y) == BUTTON_UP)
			{
				bDragging = false;
				x = 0;
				num = 0;
			}
			else
			{
				if ((mouse_location.x != old_mouse_location.x) && (mouse_location.y != old_mouse_location.x))
				{
					shapesList[x]->Resize_By_Drag(num, old_mouse_location, mouse_location);
					old_mouse_location.x = mouse_location.x;
					old_mouse_location.y = mouse_location.y;
				}
			}

		}

		// Update the screen buffer
		pUI->update_buffer();
		pUI->PrintMessage("resizing is on");
	}

	for (int i = 0; i < shapesList.size(); i++)
	{
		shapesList[i]->set_resizing(false);
	}
	pUI->set_Buffering(false);
}



vector <shape*> Graph::GetShapesList() const
{
	return shapesList;
}

void Graph::select(action temp)
{
	if (temp.get_mouse_click() == LEFT_CLICK)
	{
		for (int i = 0; i < shapesList.size(); i++)
		{
			shapesList[i]->SetSelected(false);
		}
		shape* x = Getshape(temp.Get_Point().x, temp.Get_Point().y);
		if (x != NULL)
		{
			x->SetSelected(true);
		}
	}

	else if (temp.get_mouse_click() == RIGHT_CLICK)
	{
		shape* x = Getshape(temp.Get_Point().x, temp.Get_Point().y);
		if (x != NULL)
		{
			x->SetSelected(true);
		}
	}
}

void Graph::change_draw_clr(GUI* pUI,color temp)
{
	int counter = 0;
	for (int i = 0; i < shapesList.size(); i++)
	{
		if (shapesList[i]->IsSelected())
		{
			shapesList[i]->ChngDrawClr(temp);
			counter++;

			for (int k = 0; k < shapesList.size(); k++)
			{
				if ((shapesList[i] != shapesList[k]) && (shapesList[i]->check_id(shapesList[k])))
				{
					shapesList[k]->ChngDrawClr(temp);
				}
			}


		}
	}

	if (counter != 0)
		return;

	pUI->SetCrntDrawColor(temp);

}


void Graph::change_fill_clr(GUI* pUI, color temp)
{
	int counter = 0;
	for (int i = 0; i < shapesList.size(); i++)
	{
		if (shapesList[i]->IsSelected())
		{
			shapesList[i]->ChngFillClr(temp);
			counter++;

			for (int k = 0; k < shapesList.size(); k++)
			{
				if ((shapesList[i] != shapesList[k]) && (shapesList[i]->check_id(shapesList[k])))
				{
					shapesList[k]->ChngFillClr(temp);
				}
			}


		}
	}

	if (counter != 0)
		return;

	pUI->SerCrntfillColor(temp);

}

void Graph::Delete(GUI* pUI)
{
	vector <int> to_be_deleted;
	for (int i = 0; i < shapesList.size(); i++)
	{
		if (shapesList[i]->IsSelected())
		{
			delete shapesList[i];
			to_be_deleted.push_back(i);
		}
	}

	for (auto x : to_be_deleted)
	{
		shapesList.erase(shapesList.begin() + x);
		for (int i = 0; i < to_be_deleted.size(); i++)
		{
			to_be_deleted[i] = to_be_deleted[i] - 1;
		}
	}

}

void Graph::Exit(GUI* pUI)
{
	for (int i = 0; i < shapesList.size(); i++)
	{
		delete shapesList[i];
	}
	for (int i = 0; i < play_cards.size(); i++)
	{
		delete play_cards[i];
	}
	shapesList.clear();
	play_cards.clear();
}


void Graph::Scramble()
{
	srand(time(0));
	Point temp;
	for (int i = 0; i < shapesList.size(); i++)
	{
		temp.x = (rand() % (1200 - 100 + 1)) + 100;
		temp.y = (rand() % (600 - 150+1)) + 50;

		shapesList[i]->move_to_center(temp);
	}
}

void Graph::Scramble_shapes_in_play()
{
	vector<shape*> temp;
	for (int i = 0; i < shapesList.size(); i++)
	{
		temp.push_back(shapesList[i]);
	}

	vector<int> done;
	int number = temp.size();
	srand(time(0));
	for (int i = 0; i < temp.size(); i++)
	{
		int random = rand() % number;
		while (std::count(done.begin(),done.end(),random))
		{
			random = rand() % number;
		}
		shapesList[random] = temp[i];
		done.push_back(random);
	}
}

void Graph::Matsh_Shapes(GUI* pUI)
{
	static int score = 0;
	action temp = pUI->Get_current_action_info();
	int counter = 0;
	Card* c1;
	Card* c2;
	int c_1;
	int c_2;

	for (int i = 0; i < play_cards.size(); i++)
	{
		if (play_cards[i]->IsPointInside(temp.Get_Point().x,temp.Get_Point().y ))
		{
			play_cards[i]->set_covered(false);
			Draw(pUI);
			c1 = play_cards[i];
			c_1 = i;
			counter++;
			break;
		}
	}

	if (counter == 0)
	{
		return;
	}

	Point t;
	pUI->GetPointClicked(t.x,t.y);
	bool r = false;
	while (r == false)
	{
		for (int i = 0; i < play_cards.size(); i++)
		{
			if (play_cards[i]->IsPointInside(t.x, t.y) && play_cards[i] != c1)
			{
				play_cards[i]->set_covered(false);
				Draw(pUI);
				c2 = play_cards[i];
				r = true;
				c_2 = i;
				break;
			}
		}
		if (r == true)
		{
			break;
		}
		pUI->GetPointClicked(t.x, t.y);
	}


	if (c1->check_card(c2))
	{
		Sleep(1000);
		score += 3;
		pUI->PrintMessage("Score: " + to_string(score) + "   Good Job.");
		delete play_cards[c_1];
		delete play_cards[c_2];

		play_cards.erase(play_cards.begin() + c_1);
		if (c_1 > c_2)
		{
			play_cards.erase(play_cards.begin() + c_2);
		}
		else
		{
			play_cards.erase(play_cards.begin() + (c_2 - 1));
		}
		if (play_cards.size() == 0)
		{
			score = 0;
		}

	}
	else
	{
		Sleep(1000);
		c1->set_covered(true);
		c2->set_covered(true);
		score += 1;
		pUI->PrintMessage("Score: " + to_string(score) + "   Try Again.");
	}




}


void Graph::Paste(GUI* pUI)
{
	Point t;
	pUI->GetPointClicked(t.x, t.y);

	for (int j = 0; j < copied_shapes.size(); j++)
	{
		shape* temp;
		if (dynamic_cast<Rect*> (copied_shapes[j]))
		{
			Rect* x = dynamic_cast<Rect*> (copied_shapes[j]);
			temp = new Rect(x);
		}
		else if (dynamic_cast<Square*> (copied_shapes[j]))
		{
			Square* x = dynamic_cast<Square*> (copied_shapes[j]);
			temp = new Square(x);
		}
		else if (dynamic_cast<Line*> (copied_shapes[j]))
		{
			Line* x = dynamic_cast<Line*> (copied_shapes[j]);
			temp = new Line(x);
		}
		else if (dynamic_cast<Triangle*> (copied_shapes[j]))
		{
			Triangle* x = dynamic_cast<Triangle*> (copied_shapes[j]);
			temp = new Triangle(x);
		}
		else if (dynamic_cast<Circle*> (copied_shapes[j]))
		{
			Circle* x = dynamic_cast<Circle*> (copied_shapes[j]);
			temp = new Circle(x);
		}
		else if (dynamic_cast<Group*> (copied_shapes[j]))
		{
			Group* x = dynamic_cast<Group*> (copied_shapes[j]);
			temp = new Group(x);
		}
		else if (dynamic_cast<IrregularPolygon*> (copied_shapes[j]))
		{
			IrregularPolygon* x = dynamic_cast<IrregularPolygon*> (copied_shapes[j]);
			temp = new IrregularPolygon(x);
		}

		shapesList.push_back(temp);
		temp->move_to_center(t);
	}
}



void Graph::Copy(GUI* pUI)
{
	copied_shapes.clear();

	int num = shapesList.size();
	for (int i = 0; i < num; i++)
	{
		if (shapesList[i]->IsSelected())
		{
			copied_shapes.push_back(shapesList[i]);
		}
	}

}

void Graph::Dublicate()
{
	shape* temp;
	int num = shapesList.size();
	int y = 0;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < shapesList.size(); j++)
		{
			if (shapesList[i]->check_id(shapesList[j]) && (i != j))
			{
				y = 1;
			}
		}
		if (y == 0)
		{
			if (dynamic_cast<Rect*> (shapesList[i]))
			{
				Rect* x = dynamic_cast<Rect*> (shapesList[i]);
				temp = new Rect(x);
			}
			else if (dynamic_cast<Square*> (shapesList[i]))
			{
				Square* x = dynamic_cast<Square*> (shapesList[i]);
				temp = new Square(x);
			}
			else if (dynamic_cast<Line*> (shapesList[i]))
			{
				Line* x = dynamic_cast<Line*> (shapesList[i]);
				temp = new Line(x);
			}
			else if (dynamic_cast<Triangle*> (shapesList[i]))
			{
				Triangle* x = dynamic_cast<Triangle*> (shapesList[i]);
				temp = new Triangle(x);
			}
			else if (dynamic_cast<Circle*> (shapesList[i]))
			{
				Circle* x = dynamic_cast<Circle*> (shapesList[i]);
				temp = new Circle(x);
			}
			else if (dynamic_cast<Group*> (shapesList[i]))
			{
				Group* x = dynamic_cast<Group*> (shapesList[i]);
				temp = new Group(x);
			}
			else if (dynamic_cast<IrregularPolygon*> (shapesList[i]))
			{
				IrregularPolygon* x = dynamic_cast<IrregularPolygon*> (shapesList[i]);
				temp = new IrregularPolygon(x);
			}
			shapesList.push_back(temp);
		}
		y = 0;
	}
}


void Graph::clear_cards()
{
	for (int i = 0; i < play_cards.size(); i++)
	{
		delete play_cards[i];
	}
	play_cards.clear();
}

void Graph::Start_Game(GUI* pUI)
{
	int score = 0;
	pUI->PrintMessage("Score: " + to_string(score));
	if (play_cards.size() == 0)
	{
		Dublicate();
		Scramble_shapes_in_play();
		vector<Point> x;
		Point p1;
		p1.x = 350;
		p1.y = 170;
		x.push_back(p1);
		int y = 1;
		for (int i = 0; i < shapesList.size(); i++)
		{
			Card* temp = new Card(shapesList[i], x[i]);
			play_cards.push_back(temp);
			p1.x = p1.x + 100;
			if (x.size() / 6.0 == y)
			{
				y++;
				p1.y = p1.y + 120;
				p1.x = 350;
			}
			x.push_back(p1);
			if (play_cards.size() == 24)
			{
				break;
			}
		}
	}
}

void Graph::Restart_Game(GUI* pUI)
{
	clear_cards();
	Start_Game(pUI);
}

