#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"
#include "..\Enemies\Enemy.h"

#include <string>
using namespace std;

class GUI
{

private:
	window * pWind;

	// Some Static Constant Data Members: ---------------------

	static const int
		WindWidth = 1330, WindHeight = 756,		//Window width and height
		StatusBarHeight = 100,	//Status Bar Height
		MenuBarHeight = 50,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 80,		//Width of each item in menu bar menu

		BattleAreaHeight = WindHeight - MenuBarHeight - StatusBarHeight,
		YHalfBattleArea = MenuBarHeight + BattleAreaHeight / 2, //The y coordinate of half the Battle area

		CastleStartX = WindWidth * 0.4, //The x coordinate of the upper left corner of the castle
		CastleEndX = WindWidth * 0.6,   //The x coordinate of the lower right corner of the castle

		CastleWidth = CastleEndX - CastleStartX, //The width of the castle (Note: the castle is a Square)

		CastleStartY = YHalfBattleArea - CastleWidth / 2, //The y coordinate of the upper left corner of the castle
		CastleEndY = YHalfBattleArea + CastleWidth / 2,   //The y coordinate of the lower right corner of the castle

		EnemyWidth = (WindWidth - CastleWidth - (MaxDistance * 2)) / (MaxDistance * 2),
		// the width of the enemy to make 60 unit distance 
		// from the enemy to the tower of its region
		// and 1 blank pixel between each consecutive enemies: ((MaxDistance*2) in numurator)
		EnemyHeight = (BattleAreaHeight - ((MaxVerticaEnemies + 1) * 2)) / ((MaxVerticaEnemies + 1) * 2); // the height of the enemy 
																										  // to make any region carry 15 enemies + 1 for more space
																										  // also 1 blank pixel between vertical enemies

																										  // 
																										  // TODO: Add more members if needed
																										  //

	void DrawEnemy(const Enemy & E, int YPos) const;	//draws one enemy - is not needed to be public

public:
	GUI();
	~GUI();

	// Input Functions  ---------------------------
	void GetPointClicked(Point &P) const; // waits a user click from the user
	string GetString() const; // reads a string (keyboard input) from the user

							  // Output Functions  ---------------------------
	void PrintMessage(string msg,float line=0.1) const; // prints a message in the status bar
	void DrawString(const int iX, const int iY, const string Text); // prints a message in the passed coordinates

	void DrawMenu() const;	// draws the game menu

							///////////////////////////////////////////////////////////////////
	void DrawSplashScreen() const; //splash screen function Nader
	void DrawBackground() const; // draws the sand Nader
	void ClearMenuBar() const; //betsheel 7eta mn el splashscreen Nader
							   ////////////////////////////////////////////////////////////////////

	void ClearStatusBar() const;    // clears the status bar
	void ClearBattleArea(int,int,int,int ) const;	// clears the Battle area from all drawn enemies

	void DrawCastle() const;	    // draws the castle with the towers and 4 regions
	void DrawEnemies(Enemy* enemies[], int size) const;
	void drawpavedArea(int x1, int y1,int x2,int y2)const;

	

	int getMenuBarHeight();
	int getMenuBarItemWidth();
	int getGUIHeight();
	int getStatusBarHeight();
	int getBattleAreaHeight();
	clicktype WaitMouseClick(int &iX, int &iY);
	// No matter what list type you are using to hold enemies, 
	// you must pass the enemies to the DrawEnemies as an array of enemy pointers. 
	// At every time step, you should update those pointers 
	// to point to the current active enemies 
	// then pass the pointers list to this function
};

