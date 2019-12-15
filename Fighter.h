#pragma once
#include "Enemies\Enemy.h"

class Fighter : public Enemy
{
	static const int K =1;
public:
	Fighter(int id,int arrival, int EnemyHealth, int fire, int reload,int s,REGION r_region);
	void DamageToEnemy(int TowerfirePow ); 
	void DecrementDist(int);


	~Fighter(void);
};

