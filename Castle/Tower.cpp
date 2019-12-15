#include "Tower.h"
#include<mmsystem.h>
#include<mciapi.h>
Tower::Tower (int health, int numEnemies, float fire)
{
	Health= health ;
	MaxNumberOfAttacked= numEnemies;
	ActualAttacked=0;
	FirePower= fire;
	ShootedEnemy= new Enemy*[numEnemies];
	FighterCount=0;
	ShieldedCount=0;
	KilledCount=0;
	killedEnemy=new qeueu<Enemy*>();
	PavedDistance=30;
}
qeueu<Enemy*>* Tower::getKilledQueue() {
	return killedEnemy;
}
void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return Health;
}
void Tower::setNumberOfAttack( int n)
{
	MaxNumberOfAttacked= n;
}
int Tower::getNumberOfAttacked() const
{
	return MaxNumberOfAttacked;
}

void Tower::setFirePower( float fire) 
{
	FirePower= fire;
}
float Tower::getFirePower() const
{
	return FirePower;
}

void Tower::DamageToTower() {
	node<Enemy*> * ptr;
	node<Enemy*> * ptr1;
	ptr = FighterAndPaverList.gethead();
	ptr1 = ShieldedBag.gethead();
	while (ptr) {
		if (ptr->getvalue()->getType() == 0 && ptr->getvalue()->gettimetoshoot()==0)    // True : Paver
			if (ptr->getvalue()->GetDistance() <= getPavedDistance() && ptr->getvalue()->GetDistance() > 2 && PavedDistance>2) {
				IncreasePavedDistance(ptr->getvalue()->getFirePower());
			}
			
		
		else if(ptr->getvalue()->gettimetoshoot()==0)
		{
			float H1 = Health - (1.0 / (ptr->getvalue()->GetDistance())) * (ptr->getvalue()->getFirePower());
			SetHealth(H1);

		}
		ptr = ptr->getnext();
	}

	while (ptr1 ) {
		if(ptr1->getvalue()->gettimetoshoot()==0)// Shielded Fighter
		{
			float H2 = Health - (2.0 / (ptr1->getvalue()->GetDistance())) * (ptr1->getvalue()->getFirePower());
			SetHealth(H2);
	     }
		ptr1 = ptr1->getnext();
	}
	
}
void Tower::IncreasePavedDistance(int p) {
	if (PavedDistance < p )  //////////////&& PavedDistance<2
	{
		PavedDistance = 2;
		return;
	}
	else if(PavedDistance-p>=2)
		PavedDistance -= p;
	else 
		PavedDistance = 2;
}

bool Tower::TowerWon() {
	if (ShieldedBag.gethead() == NULL && FighterAndPaverList.gethead() == NULL) {
		return true;
	}
	return false;
}

void Tower::AddFighterToList(Enemy*  ptr)
{
	FighterAndPaverList.add(ptr);
	FighterCount++;
}
void Tower::AddShieldedToList (Enemy* ptr)
{
	ShieldedBag.add(ptr);
	ShieldedCount++;
}



Tower::~Tower()
{
	FighterAndPaverList.clear();
	ShieldedBag.clear();
	killedEnemy->clear();
}


void Tower::CheckIfKilled (int time) ///////////////////////////////////////////////////////////////////////////////////// this will be modified in ohase 2   	
	// pass on the shooted array, if health= 0, move it to killed function
{
	for(int i=0 ; i<ActualAttacked ; i++)
	{
		ShootedEnemy[i]->DamageToEnemy(getFirePower());	
	}

	for(int i=0 ; i<ActualAttacked ; i++)
	{
		if(ShootedEnemy[i]->getHealth()<=0)
			addKilled(ShootedEnemy[i],time);
	}

}

void Tower::addKilled(Enemy* killed,int time) 
{ 
	PlaySound("heartbeat.wav", NULL, SND_ASYNC);
	Sleep(1000);
	killed->setState(0);
	killed->setKilledTimeStep(time);
	killedEnemy->enqueue(killed);
	KilledCount++;
	if(killed->getType()==2)
	{
		ShieldedBag.remove(killed);
		ShieldedCount--;
	}
	else{
		FighterAndPaverList.remove(killed);
		FighterCount--;

	}
}
int Tower::getFighterCount(){
	return FighterCount;
}
int Tower::getShieldedCount(){
	return ShieldedCount;
}
void Tower::moveEnemies()
{
	node<Enemy*>*e=FighterAndPaverList.gethead();
	while (e)
	{ 

		if(e->getvalue()->GetDistance() >= PavedDistance+ e->getvalue()->getspeed())
		{
			e->getvalue()->DecrementDist(PavedDistance);
		}
		e->getvalue()->decreaceTimeToShoot();
		e=e->getnext();
	}
	e=ShieldedBag.gethead();
	while (e)
	{   
		if(e->getvalue()->GetDistance() >= getPavedDistance()+ e->getvalue()->getspeed())
		{   
			e->getvalue()->DecrementDist(0);
		}
		e->getvalue()->decreaceTimeToShoot();
		e=e->getnext();
	}
}
int Tower::getKilledCount(){
	return KilledCount;
}

int Tower::getPavedDistance() {
	return PavedDistance;
}


node<Enemy* > * Tower:: getFighterHead()
{
	return FighterAndPaverList.gethead();
}

node<Enemy* > * Tower:: getShieldedHead()
{
	return ShieldedBag.gethead();
}

void Tower::AddToShooted (int t)

{ 
	if ( Health!=0)
	{
	for (int i=0;i<MaxNumberOfAttacked;i++)
			ShootedEnemy[i]=NULL;
	node<Enemy* > *ptr= FighterAndPaverList.gethead();
	if (MaxNumberOfAttacked > (FighterCount+ ShieldedCount))
	{
		ActualAttacked= FighterCount+ ShieldedCount;
		for (int i=0; i<FighterCount ; i++)
		{
			if(ptr){
			ShootedEnemy[i]= ptr->getvalue();
			ptr->getvalue()->setfirstshouttime(t);
			}
			ptr= ptr->getnext();
		}
		ShieldedBag.Sort();
		ptr= ShieldedBag.gethead();
		for (int i=FighterCount; i< (FighterCount+ShieldedCount) ; i++) 
		{
			if(ptr){
			ShootedEnemy[i]= ptr->getvalue();
			ptr->getvalue()->setfirstshouttime(t);
			}
			ptr= ptr->getnext();
		}
		
	}

	else if (ShieldedCount >= MaxNumberOfAttacked )
	{
		ActualAttacked= MaxNumberOfAttacked;
		ShieldedBag.Sort();
		ptr= ShieldedBag.gethead();
		for (int i=0; i<MaxNumberOfAttacked ; i++)
		{
			if (ptr)
			{
				ShootedEnemy[i]= ptr->getvalue();
				( ptr->getvalue() )->setfirstshouttime(t);
			}
			ptr= ptr->getnext();
		}

	}

	else 
	{
		ActualAttacked= MaxNumberOfAttacked;
		ShieldedBag.Sort();
		ptr= ShieldedBag.gethead();
		
		for (int k=0; k<ShieldedCount ; k++)
		{    if (ptr){
			ShootedEnemy[k]= ptr->getvalue();
			( ptr->getvalue() )->setfirstshouttime(t);
		}
		     ptr= ptr->getnext();
		}
		ptr= FighterAndPaverList.gethead();
		for (int j=ShieldedCount; j<MaxNumberOfAttacked ; j++)
		{
			if(ptr){
			ShootedEnemy[j]= ptr->getvalue();
			( ptr->getvalue() )->setfirstshouttime(t);
			}
			ptr= ptr->getnext();
		}
	}
	}

}

void Tower :: ClearFighter()
{
	FighterAndPaverList.clear();
}

void Tower:: ClearShielded()
{
	ShieldedBag.clear();
}

void Tower::DamageToEnemyyy()
{
	for (int i=0; i< ActualAttacked ; i++)
		ShootedEnemy[i]->DamageToEnemy(FirePower);
}

void Tower::setFighterCount (int count)
{
    FighterCount=count;
}
void Tower::setShieldedCount (int count)
{
	ShieldedCount= count;
}