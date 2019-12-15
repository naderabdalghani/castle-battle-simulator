#pragma once
#include "Enemies\Enemy.h"

class Paver:public Enemy
{
	static const int K =1;
public:
	Paver(int id,int arrival, int EnemyHealth, int fire, int reload,int s ,REGION r_region);
	void DamageToEnemy(int TowerfirePow ); 
	void DecrementDist(int);


	~Paver(void);
};

