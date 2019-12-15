#include "Paver.h"


Paver:: Paver (int id,int arrival, int EnemyHealth, int fire, int reload,int s,REGION r_region): 
	Enemy(id,arrival, EnemyHealth, fire, reload,s, r_region,DARKBLUE,0)
{}


void Paver::DamageToEnemy(int TowerfirePow )
{
	Health= Health- ((1.0/ Distance)* TowerfirePow* (1.0));
}

Paver::~Paver(void)
{
}

void Paver::DecrementDist(int paved)
{
	if (Distance+speed > MinDistance  ){
		if (gettimetoshoot()!=0 && paved+speed<= Distance )
			Distance-=speed;
		else if(gettimetoshoot()==0 && paved < Distance-FirePower)
		{
			Distance-=FirePower;
		}
		else if(gettimetoshoot()==0 && paved >= Distance-FirePower)
			Distance=paved;
		 else if(Distance-FirePower<2 )
				 Distance=MinDistance;
	}
	else 
		Distance=MinDistance;
}
