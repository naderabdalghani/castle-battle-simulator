#include "Enemy.h"

// ADDED //
void Enemy::setspeed(int s)
{
	speed=s;
}
int Enemy::getspeed()
{
	return speed;
}
Enemy:: Enemy(int id,int arrival, int EnemyHealth, int fire, int reload,int s,REGION r_region,color r_c, int typ ,int d  )
{
	speed=s;
	ID =id;
	ArrivalTime= arrival; 
	Region= r_region;
	Health= EnemyHealth;
	FirePower= fire;
	ReloadPeriod= reload;
	SetDistance(d);
	Type = typ;
	FirstShotDelay=-1;
	killedTimeStep=-1;
	firstshottime=-1;
	timeToShoot=0;


	Clr =r_c;    //Assigning the proper image to an enemy at construction Nader
	if (Clr == DARKBLUE) {
		clr = "images\\Enemies\\Paver.jpg";
	}
	else {
		if (Clr == ORANGERED) {
			clr = "images\\Enemies\\Shielded.jpg";    
		}
		else { clr = "images\\Enemies\\Fighter.jpg"; }
	} 
}
Enemy :: Enemy()
{
}
Enemy::~Enemy()
{
}
int Enemy::getID() const {
	return ID;
}


color Enemy::GetColor() const  //Modified Nader
{
	return Clr;
}

REGION Enemy::GetRegion() const
{
	return Region;
}


void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance()const 
{
	return Distance;
}
int Enemy::getArrivalTime() const
{
	return ArrivalTime;
}

void Enemy::setFirePower( int fire)
{
	FirePower= fire;
}

int  Enemy::getFirePower() const 
{
	return FirePower;
}
int Enemy:: getState() const 
{
	return state;
}

void Enemy:: setState(int s)
{
	state= s;
}

void Enemy::setHealth (int hlth)
{
	Health=  hlth;
}
int Enemy::getHealth ()
{
	return Health;
}
int Enemy::ToShoot() 
{return -timeToShoot;}

int Enemy::getType ()
{
	return Type;
}


bool Enemy::operator==(const Enemy & enemy)
{
	return ID==enemy.ID;
}
bool Enemy::operator==(const Enemy* & enemy)
{
	return ID==enemy->getID();
}
bool Enemy::operator >(const Enemy* & rhs)
{
	if(FirstShotDelay>rhs->getFirstShotDelay())
		return true;
	else 
		return false;

}
bool Enemy::operator < (const Enemy* & rhs)
{
	if(FirstShotDelay < rhs->getFirstShotDelay())
		return true;
	else 
		return false;
}

void Enemy::setFirstShotDelay() 
{
	FirstShotDelay=firstshottime-ArrivalTime;
}


int Enemy::getfirstshottime()
{
	return firstshottime;
}
int Enemy::getKilledTimeStep() const {
	return killedTimeStep;
}
void Enemy::setKilledTimeStep(int currentTimeStep) {
	killedTimeStep = currentTimeStep;
}
int Enemy::getFirstShotDelay() const {
	return firstshottime-ArrivalTime;

}	
int Enemy::getKilledDelay() const {
	return killedTimeStep-firstshottime;
}
int Enemy::getLifeTime() const {
	return killedTimeStep-ArrivalTime;
}

void Enemy:: setarrivaltime(int arrt)
{
	ArrivalTime=arrt;
}

void Enemy::setfirstshouttime(int fst)
{
	if (firstshottime == -1 )
	   firstshottime=fst;
}

int Enemy::gettimetoshoot(){
	return timeToShoot;
}
void Enemy::decreaceTimeToShoot(){
	if(timeToShoot==0)
		timeToShoot-=ReloadPeriod;
	else
		timeToShoot++;
}

void Enemy::setRegion(REGION r)
{
	Region= r;
}

