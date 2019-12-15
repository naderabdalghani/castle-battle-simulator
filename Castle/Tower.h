#pragma once
#include "../Enemies/Enemy.h"
#include "../node.h"
#include "../qeueu.h"
#include "../linkedlist.h"

class Tower
{
	double Health;
	// ADDED // 
	int MaxNumberOfAttacked;                    // max number a tower can attack 
	int ActualAttacked;                         //actual number the tower will attack
	float FirePower;
	linkedlist < Enemy* >  FighterAndPaverList; // linkedlist of present fighers and pavers
	linkedlist < Enemy* > ShieldedBag;         // elmafrod bag !
    Enemy*  *ShootedEnemy;    // array of enemies the tower will shoot
	int FighterCount;                         // temporary for phase 1
	int ShieldedCount;                        // temporary for phase 1
	int PavedDistance; //Nader

	 int KilledCount; /// added 2
	 qeueu<Enemy*> * killedEnemy; ////////////// added 
	//
	// TODO: Add More Data Members As Needed
	//

public:
	// ADDED //
	Tower() {}
	Tower (int health, int numEnemies, float fire);

	void SetHealth(double h);
	double GetHealth() const;

	// ADDED //
	void setFighterCount (int count);
	void setShieldedCount (int count);
	void setNumberOfAttack( int n);
	int getNumberOfAttacked() const;
	void setFirePower(float fire) ;
	float getFirePower() const;
	void AddFighterToList(Enemy*  ptr);
	void AddShieldedToList(Enemy*  ptr);
	void DamageToTower(); //Nader
	void CheckIfKilled (int);///////////////////////////////////////////////////////////
	node<Enemy* > * getFighterHead();
	node<Enemy* > * getShieldedHead();
	int getKilledCount();
	qeueu<Enemy*>* getKilledQueue();
	void AddToShooted (int t);  //M//
	~Tower();

	void addKilled(Enemy* ,int) ;//////////////////////////////////////////////////////
	void moveEnemies();
	//
	// TODO: Add More Member Functions As Needed
	//
	int getPavedDistance(); //Nader
	void IncreasePavedDistance(int p);//Nader
	bool TowerWon();  //Nader
	void ClearFighter(); //M//
	void ClearShielded(); //M//
	void DamageToEnemyyy(); //M//
	int getFighterCount();
	int getShieldedCount();

};

