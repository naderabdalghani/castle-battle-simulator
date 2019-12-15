#include "Shielded.h"
double Shielded::c1=0;
double Shielded::c2=0;
double Shielded::c3=0;
Shielded::Shielded(int id,int arrival, int EnemyHealth, int fire, int reload,int s,REGION r_region): 
	Enemy(id,arrival, EnemyHealth, fire, reload,s, r_region,ORANGERED,2)
{}


float Shielded::Priority()
{
	return (getFirePower()/GetDistance())*c1+c2/(1+ToShoot())+c3*getHealth();
}
void Shielded::setConst(double a,double b,double c)
{
	c1=a;
	c2=b;
	c3=c;
}
Shielded::~Shielded(void)
{
}
bool Shielded::operator <=(Shielded * E){

	return Priority()<E->Priority();

}

void Shielded::DamageToEnemy(int TowerfirePow )
{
	Health= Health- ((1.0/ Distance)* TowerfirePow* (1.0));
}
void Shielded::DecrementDist(int d)
{
	if (Distance+speed > MinDistance)
		Distance-=speed;
	else
		Distance=MinDistance;
}

