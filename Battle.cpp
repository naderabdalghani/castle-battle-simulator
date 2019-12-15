#include "Battle.h"
#include "InteractiveAction.h"
#include "StepAction.h"
#include "SilentAction.h"
#include<mmsystem.h>
#include<mciapi.h>
Battle::Battle(GUI *p)
{
	EnemyCount = 0;
	killedcount=0;
	IndexForActive=0;
	IndexFordraw=0;
	for (int i=0;i<MaxEnemyCount;i++)
	{
		ForDraw[i]=NULL;
		inputEnemies[i]=NULL;
	}
	GameIsWon = true;
	win=false;
	loss=false;
	finalofgame=true;
	pIn = new Input(p);
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount) 
	{
		inputEnemies[EnemyCount++] = Ptr;
		
	}

}
bool Battle::SilentBattleSimulation(int timestep) 
{
	pIn->getpWind()->PrintMessage(" Silent Mode is actived");
	ChangeToActive(timestep);
	damagetocastle();
	SwitchEnemies();
	moving();
	Kill(timestep);
	BCastle.settotalShotDelayKilled();

	setwin();
	setloss();
	setfinalofgame();
	return getfinalofgame();

}

void Battle::drawPaveddis (Tower*t,GUI*& pGame){
	
	int paved0 =t[0].getPavedDistance();
	int paved1 =t[1].getPavedDistance();
	int paved2 =t[2].getPavedDistance();
	int paved3 =t[3].getPavedDistance();
	pGame->ClearBattleArea(paved0,paved1,paved2,paved3);
	pGame->DrawCastle();
	
	
}
void Battle::printinfo(GUI*& pGame ){

	pGame->ClearStatusBar();
	pGame->PrintMessage(BCastle.regionsHealth(),.2);
	pGame->PrintMessage(BCastle.regionsEnemies(),.5);
	pGame->PrintMessage(BCastle.Killed(),1.1);

}
bool Battle::BattleSimulation(GUI*& pGame ,int timestep) 
{
	printinfo(pGame);
	drawPaveddis(BCastle.gettowers(),pGame);
	DrawEnemies(pGame,timestep);
	damagetocastle();
	SwitchEnemies();
	moving();
	Kill(timestep);
	BCastle.settotalShotDelayKilled();
	printinfo(pGame);
	setwin();
	setloss();
	setfinalofgame();
	return getfinalofgame();
}

 void Battle::setfinalofgame()
 {
	 if(win||loss)
		 finalofgame=false;

 }
bool Battle::getfinalofgame()
{
	return finalofgame;
}
void Battle::setwin()
{
	if (getKilled()==EnemyCount)
		win=true;

}
bool Battle::getwin()
{
	return win;
}
void Battle::setloss()
{   Tower* t=BCastle.gettowers();
    double health=0;
	for(int i=0 ;i<4;i++)
		health+=t[i].GetHealth();
	if (health==0)
		loss=true;

}
bool Battle::getloss()
{
	return loss;
}

int Battle::getEnemyCount() const {
	return EnemyCount;
}




void Battle::DrawEnemies(GUI *& pGUI, int time)
{   
	ChangeToActive(time);
    fillForDraw();
	pGUI->DrawEnemies(ForDraw,IndexFordraw);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::ChangeToActive (int TimeStep)
{
	while (inputEnemies[IndexForActive]!=NULL)
	{
		if (inputEnemies[IndexForActive]->getArrivalTime() == TimeStep)
		{
		BCastle.AddEnemyToTower(inputEnemies[IndexForActive]);
	     IndexForActive++;
		}
		else
			break;
	}
		
}

void Battle::Kill (int time)
{
	Tower *t=BCastle.gettowers();
	for( int i=0; i< NoOfRegions ; i++ )
	{
		if(t[i].GetHealth()!=0){
		t[i].AddToShooted(time);
		t[i].DamageToEnemyyy();
		t[i].CheckIfKilled(time);
		}
	}
}
void Battle::damagetocastle()
{
	Tower *t=BCastle.gettowers();
	for(int i=0; i<NoOfRegions;i++)
	{
		t[i].DamageToTower();
	}
	if(IndexFordraw!=0)
	{
		PlaySound("shot.wav", NULL, SND_ASYNC);
		Sleep(1500);
	}
}

int Battle::getKilled (){
	Tower *t=BCastle.gettowers();
	killedcount=0;
	for (int i=0;i<4;i++)
		killedcount+=t[i].getKilledCount();
	return killedcount;
}
int Battle::getActive ()
{ return IndexFordraw;}
void Battle::moving()
{
	Tower *t=BCastle.gettowers();
	for (int i=0;i<4;i++)
		t[i].moveEnemies();
	
}
void Battle::fillForDraw()
{
	Tower *t= BCastle.gettowers() ;
	int j=0;
	IndexFordraw=0;
	for (int i=0;i<MaxEnemyCount;i++)
		ForDraw[i]=NULL;
	for (int i=0;  i< NoOfRegions ; i++)
	{  
		
	    node<Enemy*>* p=t[i].getFighterHead();
		while (p)
		{  if (p->getvalue()->getState()!=0){
			ForDraw[j++]=p->getvalue();
			IndexFordraw++;
		}
			p=p->getnext();
		}
		p=t[i].getShieldedHead();
		while (p)
		{  if (p->getvalue()->getState()!=0){
			ForDraw[j++]=p->getvalue();
			IndexFordraw++;
		}
			p=p->getnext();
		}

	}
}	


ActionType Battle::GetUserAction() const {
	return pIn->GetUserAction();
}
void Battle::ExecuteAction(GUI*& pGUI,ActionType ActType) {
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case MENU_LOAD:
		break;

	case MENU_INTERACTIVE:
		pAct = new InteractiveAction(this);
		break;

	case MENU_STEP:
		pAct = new StepAction(this);
		break;

	case MENU_SILENT:
		pAct = new SilentAction(this);
		break;


	case MENU_EXIT:

		break;

	case STATUS:	//a click on the status bar ==> no action
		return;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(pGUI);//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
Input* Battle::GetInput() const {
	return pIn;
}


void Battle::setavrfiristshotdelay(int newadd)
{
	avrfirstshotdelay+= newadd;
}
void Battle::setavrkilldelay(int newadd)
{
	avrkilldelay += newadd;
}
int Battle::getavrfiristshotdelay()
{
	return avrfirstshotdelay;
}
int Battle::getavrkilldelay()
{
	return avrkilldelay;
}

void Battle::SwitchEnemies()
{
	BCastle.CastleSwitch();
}


float Battle::AverageFD()
{
	float totalfristshotDelay=BCastle.getTotalFirstShotDelayKilled ();
	int totalNO =BCastle.getTotalNumberOfKilledshooted();
	Tower*t=BCastle.gettowers();
	for (int i=0;i<4;i++){
		node<Enemy*>* ptr =t[i].getFighterHead();
		while(ptr)
		{
			totalfristshotDelay+=ptr->getvalue()->getFirstShotDelay();
			totalNO ++;
			ptr=ptr->getnext();
		}
		ptr =t[i].getShieldedHead();
		while(ptr)
		{
			totalfristshotDelay+=ptr->getvalue()->getFirstShotDelay();
			totalNO ++;
			ptr=ptr->getnext();
		}

	}
	return totalfristshotDelay/totalNO  ;
}

Battle::~Battle(){
	
}