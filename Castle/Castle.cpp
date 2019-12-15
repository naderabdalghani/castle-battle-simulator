#include "Castle.h"
#include<iostream>
#include "..\GUI\GUI.h"
using namespace std;
Castle::Castle()
{
	TotalNumberOfshooted=0;
	TotalFirstShotDelay=0;
}

void Castle::SetTowersinfo(Tower  h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i]=h;
	}
	return ;
}
void Castle::AddEnemyToTower (Enemy *ptr)
{
	REGION r =ptr->GetRegion();

	if (r== A_REG)
	{
		if (ptr->getType() == 2)
			Towers[0].AddShieldedToList(ptr);
		else 
			Towers[0].AddFighterToList(ptr);
	}

	else if (r== B_REG)
	{
		if (ptr->getType() == 2)
			Towers[1].AddShieldedToList(ptr);
		else 
			Towers[1].AddFighterToList(ptr);
	}

	else if (r== C_REG)
	{
		if (ptr->getType() == 2)
			Towers[2].AddShieldedToList(ptr);
		else 
			Towers[2].AddFighterToList(ptr);
	}

	else if (r== D_REG)
	{
		if (ptr->getType() == 2)
			Towers[3].AddShieldedToList(ptr);
		else 
			Towers[3].AddFighterToList(ptr);
	}


}

Tower* Castle::gettowers()
{
	return Towers;
}

void Castle::CastleSwitch()
{
	for (int i=0 ; i<NoOfRegions ; i++)
	{
		if (Towers[i].GetHealth()==0)
		{
			int j = (i+1 > 3) ? 0:i+1 ; 
			int dist;
			if (Towers[i].getFighterHead())
			{
				node<Enemy*>* ptr= Towers[i].getFighterHead();

				while(ptr)
				{
					dist= (ptr->getvalue()->GetDistance() > (Towers[j].getPavedDistance() )) ? ptr->getvalue()->GetDistance() :Towers[j].getPavedDistance() ;
					ptr->getvalue() ->SetDistance(dist);
					switch (i)
					{
					        case (0):
								{
							ptr->getvalue()->setRegion(B_REG);
							break;
								}
							case (1):
								{
							ptr->getvalue()->setRegion(C_REG);
							break;
								}
							case (2):
								{
							ptr->getvalue()->setRegion(D_REG);
							break;
								}
							case (3):
								{
							ptr->getvalue()->setRegion(A_REG);
							break;
								}
					

					       default:
						   break;
					}
					Towers[j].AddFighterToList(ptr->getvalue());
					ptr= ptr->getnext();
				}
				Towers[i].ClearFighter();
				Towers[i].setFighterCount(0);
			}
			if (Towers[i].getShieldedHead())
			{
				node<Enemy*>* ptr1= Towers[i].getShieldedHead();
				while(ptr1 )
				{
					dist= (ptr1->getvalue()->GetDistance() > (Towers[j].getPavedDistance() )) ? ptr1->getvalue()->GetDistance() :Towers[j].getPavedDistance() ;
					ptr1->getvalue() ->SetDistance(dist);
					switch (i)
					{
					        case (0):
								{
							ptr1->getvalue()->setRegion(B_REG);
							break;
								}
							case (1):
								{
							ptr1->getvalue()->setRegion(C_REG);
							break;
								}
							case (2):
								{
							ptr1->getvalue()->setRegion(D_REG);
							break;
								}
							case (3):
								{
							ptr1->getvalue()->setRegion(A_REG);
							break;
								}
					

					       default:
						   break;
					}
					Towers[j].AddShieldedToList(ptr1->getvalue());
					ptr1= ptr1->getnext();
				}
				Towers[i].ClearShielded();
				Towers[i].setShieldedCount(0);
			}
		}
	}
}


void Castle::settotalShotDelayKilled()
{   
	node <Enemy*> * ptr=Towers[0].getKilledQueue()->gethead();
	while (ptr)
	{
		TotalNumberOfshooted++;
		TotalFirstShotDelay+=ptr->getvalue()->getFirstShotDelay();
		ptr=ptr->getnext();
	}
}
int Castle::getTotalNumberOfKilledshooted()
{return TotalNumberOfshooted;}
int Castle::getTotalFirstShotDelayKilled(){
	return TotalFirstShotDelay;
}
string Castle::regionsHealth(){
	return "Region A Tower's Health "+ to_string((Towers[0].GetHealth()))+"        "+"Region B Tower's Health "+ to_string((Towers[1].GetHealth()))+"        "+"Region C Tower's Health "+ to_string((Towers[2].GetHealth()))+"        "+"Region D Tower's Health "+ to_string((Towers[3].GetHealth()));
}
string Castle::regionsEnemies(){
	return "#Enemies are "+to_string(Towers[0].getFighterCount()+Towers[0].getShieldedCount())+"                                       #Enemies are "+to_string(Towers[1].getFighterCount()+Towers[1].getShieldedCount())+"                                    #Enemies are "+to_string(Towers[2].getFighterCount()+Towers[2].getShieldedCount())+"                                                #Enemies are "+to_string(Towers[3].getFighterCount()+Towers[3].getShieldedCount());
}
string Castle:: Killed(){
	return "#Killed = "+to_string(TotalNumberOfshooted);
}