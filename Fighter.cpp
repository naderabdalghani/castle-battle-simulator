#include "Fighter.h"


Fighter:: Fighter(int id,int arrival, int EnemyHealth, int fire, int reload,int s,REGION r_region): 
	Enemy(id,arrival, EnemyHealth, fire, reload,s, r_region ,DARKOLIVEGREEN,1)
{}

void Fighter::DamageToEnemy(int TowerfirePow )
{
	Health= Health- ((1.0/ Distance)* TowerfirePow* (1.0));
}

Fighter::~Fighter(void)
{
}

void Fighter::DecrementDist(int d)
{
	if (Distance+speed > MinDistance)
		Distance-=speed;
	else
		Distance=MinDistance;
}
