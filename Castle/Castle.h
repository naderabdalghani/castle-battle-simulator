#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "../qeueu.h"
#include "Tower.h"

class Castle
{
	Tower Towers[NoOfRegions];
	int TotalNumberOfshooted;
	int TotalFirstShotDelay;
	// ADDED 
	
	//
	// TODO: Add More Data Members As Needed
	//
	
public:

	Castle();
	void SetTowersinfo(Tower  h);
	void AddEnemyToTower (Enemy *ptr);
	Tower* gettowers();
	void CastleSwitch(); // switch enemies from tower to tower if the tower is dead   //M//
	void settotalShotDelayKilled();  //M//
	int getTotalNumberOfKilledshooted();
	int getTotalFirstShotDelayKilled();
	string regionsHealth();
	string regionsEnemies();
	string Killed();
};
