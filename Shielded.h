#pragma once
#include "Enemies\Enemy.h"

class Shielded: public Enemy
{
	static const int K= 2;
	static double c1;
	static double c2;
	static double c3;
public:
	Shielded(int id,int arrival, int EnemyHealth, int fire, int reload,int s,REGION r_region);
	float Priority();
	static void setConst(double,double,double);
	bool operator <=(Shielded*);
	void DamageToEnemy(int TowerfirePow ); 
	~Shielded(void);
	void DecrementDist(int);


};

