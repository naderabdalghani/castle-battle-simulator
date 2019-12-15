#ifndef INPUT_H
#define INPUT_H

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "GUI\GUI.h"


class Input		//The application manager should have a pointer to this class
{
private:
	GUI * pWind;	//Pointer to the Graphics Window
public:
	Input(GUI *pW);		//Consturctor
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	bool InBattleArea(int x, int y) const;
	ActionType GetUserAction() const; //Read the user click and map to an action
	GUI* getpWind();
	~Input();
};

#endif