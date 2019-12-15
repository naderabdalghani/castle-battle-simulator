#include "Input.h"


Input::Input(GUI * pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	Point p;
	pWind->GetPointClicked(p);
	x = p.x;
	y = p.y;
	//Wait for mouse click
}

bool Input::InBattleArea(int x, int y) const
{
	return (y > pWind->getMenuBarHeight() && y < (pWind->getGUIHeight() - pWind->getStatusBarHeight()));
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

									//[1] If user clicks on the Menubar
	if (y >= 0 && y < pWind->getMenuBarHeight())
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = 0;
		if (x <= 400) {
			ClickedItemOrder = (x / pWind->getMenuBarItemWidth());
		}
		switch (ClickedItemOrder)
		{
		case MENU_LOAD: return MENU_LOAD;
		case MENU_INTERACTIVE: return MENU_INTERACTIVE;
		case MENU_STEP:return MENU_STEP;
		case MENU_SILENT: return MENU_SILENT;
		case MENU_EXIT:return MENU_EXIT;



		default:return EMPTY;	//A click on empty place in desgin toolbar
		}
	}

	//[2] User clicks on the drawing area
	if (y >= pWind->getMenuBarHeight() && y < pWind->getGUIHeight() - pWind->getStatusBarHeight())
	{
		return BATTLE;
	}

	//[3] User clicks on the status bar
	if (y >= pWind->getGUIHeight() - pWind->getMenuBarHeight() && y < pWind->getGUIHeight())
	{
		return STATUS;
	}
}

/////////////////////////////////

Input::~Input()
{
}
GUI* Input:: getpWind()
{
	return pWind;
}