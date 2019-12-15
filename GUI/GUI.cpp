#include "GUI.h"
#include "time.h"
#include<mmsystem.h>
#include<mciapi.h>

void wait(int seconds)  //Nader
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {

	}
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth + 15, WindHeight, 0, 0);
	pWind->ChangeTitle("The Castle Game");
	DrawSplashScreen();
	ClearMenuBar();
	DrawMenu();
	DrawBackground();
	ClearStatusBar();
	ClearBattleArea(30,30,30,30);
	DrawCastle();

}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		ClearStatusBar();
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg,float line) const	//Prints a message on status bar
{
	
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/(1.0+line)), msg); // You may need to change these coordinates later 
																		   // to be able to write multi-line
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawSplashScreen() const {
	string image;
	image = "images\\SplashScreen\\SplashScreen_Image.jpg";
	PlaySound("start.wav", NULL, SND_ASYNC);
	Sleep(1000);

	int x = 0;
	while (x < 1) {
		pWind->DrawImage(image, 0, 0, WindWidth, WindHeight);
		Sleep(4000);
		x++;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];

	MenuItemImages[MENU_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[MENU_INTERACTIVE] = "images\\MenuItems\\Menu_Interactive.jpg";
	MenuItemImages[MENU_STEP] = "images\\MenuItems\\Menu_Step.jpg";
	MenuItemImages[MENU_SILENT] = "images\\MenuItems\\Menu_Silent.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//
	//TODO: Prepare images for each menu item (an icon for each modes) and add it to the list
	//

	// You should add an icon for each mode of operation (silent, step by step, ...etc.)

	//Draw menu item one image at a time
	for (int i = 0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawBackground() const {
	string image;
	image = "images\\Background\\Background.jpg";
	pWind->DrawImage(image, 0, MenuBarHeight, 1330, BattleAreaHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearMenuBar() const {
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, WindWidth, WindHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea(int paved0,int paved1,int paved2,int paved3) const
{
	DrawBackground();
	int x1=540-8*paved0;
	if(x1>=525)
		x1=525;
	int x2=790+8*paved1;
	if(x2<805)
		x2=805;
	int x3=790+8*paved2;
	if(x3<805)
		x3=805;
	int x4=540-8*paved3;
	if(x4>=525)
		x4=525;
	drawpavedArea(x1,60,525,350);
	drawpavedArea(805,60,x2,350);
	drawpavedArea(805,355,x3,650); 
	drawpavedArea(x4,355,525,650);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::drawpavedArea(int x1, int y1,int x2,int y2)const
{
	pWind->SetPen(BLACK);
	pWind->SetBrush(YELLOW);
	pWind->DrawRectangle(x1,y1,x2,y2);
}
void GUI::DrawCastle() const
{
	string image;
	image = "images\\Castle\\Towers.jpg";
	pWind->DrawImage(image, CastleStartX, CastleStartY, 266, 266);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{  
	

	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth / 2 - CastleWidth / 2);
		refY = YHalfBattleArea - 1 - EnemyWidth; //
		x = refX - Distance * EnemyWidth - Distance; //(Distance)
		y = refY - YPos * EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth / 2 + CastleWidth / 2);
		refY = YHalfBattleArea - 1 - EnemyWidth; //
		x = refX + (Distance - 1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos * EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth / 2 + CastleWidth / 2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance - 1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos - 1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth / 2 - CastleWidth / 2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance * EnemyWidth - Distance; //(Distance)
		y = refY + (YPos - 1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
	//pWind->DrawImage(image, x, y, EnemyWidth, EnemyHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for (int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
								// else print number of enemy in the region
		bool draw = true;
		for (int distance = MaxDistance; distance >= MinDistance; distance--)
		{
			CountEnemies = 0;

			for (int i = 0; i < size; i++)
			{
				if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if (CountEnemies > 15)
			{
				draw = false;
				break;
			}
		}
		if (draw)
		{
			for (int distance = MaxDistance; distance > 1; distance--)
			{
				CountEnemies = 0;

				for (int i = 0; i < size; i++)
				{
					if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region + 1) +
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}

int GUI::getMenuBarHeight() {
	return MenuBarHeight;
}
int GUI::getMenuBarItemWidth() {
	return MenuItemWidth;
}
int GUI::getGUIHeight() {
	return WindHeight;
}
int GUI::getStatusBarHeight() {
	return StatusBarHeight;
}
int GUI::getBattleAreaHeight() {
	return BattleAreaHeight;
}
clicktype GUI::WaitMouseClick(int &iX, int &iY) {
	return pWind->WaitMouseClick(iX, iY);
}
