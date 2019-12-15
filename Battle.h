#pragma once
#include "qeueu.h"
#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "Fighter.h"
#include "Paver.h"
#include "Shielded.h"
#include "Input.h"
#include "Action.h"


// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy * inputEnemies[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
	int IndexForActive;			  			// No matter what list type you are using to hold enemies, 
	Enemy * ForDraw[MaxEnemyCount];	
	int IndexFordraw;                       // you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function
	// ADDED // 
	//qeueu<Enemy*> * killedEnemy;
	int killedcount;
	linkedlist<Enemy*> ActiveEnemy;
	//
	// TODO: Add More Data Members As Needed
	//
	int avrkilldelay;
	int avrfirstshotdelay;
	bool GameIsWon; //Nader
	Input *pIn; //Nader
	bool finalofgame; //Reham
	bool win; //Reham
	bool loss;//Reham
public:
	
	Battle(GUI *p);
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * &pGUI,int);
	Castle * GetCastle();
	void ChangeToActive (int Timestep);
	int getKilled();
	int getActive();
	void Kill (int time);
	void moving();
	void fillForDraw();
	
	//
	// TODO: Add More Member Functions As Needed
	//
	int getEnemyCount() const; //Nader

				   //Application Manager Related Functions

	ActionType GetUserAction() const;
	void ExecuteAction(GUI*&,ActionType); //Creates an action and executes it
	Input* GetInput() const; //Nader

	void setavrfiristshotdelay(int newadd);
	void setavrkilldelay(int newadd);
	int getavrfiristshotdelay();
	int getavrkilldelay();
	bool BattleSimulation(GUI*& ,int); //Reham 
	bool SilentBattleSimulation(int); // Reham
	void damagetocastle();  //reham
	void setfinalofgame();//Reham
	bool getfinalofgame();//Reham
	void setwin();//Reham
	bool getwin();//Reham
	void setloss();//Reham
	bool getloss();//Reham
	void SwitchEnemies();  //M//
	float AverageFD();
	void drawPaveddis (Tower*,GUI*& pGame);
	void printinfo(GUI*&);
	~Battle();
};

