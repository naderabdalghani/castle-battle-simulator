#include "StepAction.h"
#include <time.h>
#include "Battle.h"




StepAction::StepAction(Battle *pApp): Action(pApp)
{
	
}
void StepAction::wait(int seconds)  //Nader
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {

	}
}

void StepAction::Execute(GUI*& pGUI) {
	bool flag = true;
	int time=0;
	while (flag) {
		flag = pManager->BattleSimulation(pGUI,time);
		outputFile.Append(pManager);
		time++;
		wait(1);
	}
	pManager->drawPaveddis(pManager->GetCastle()->gettowers(),pGUI);
	pGUI->ClearStatusBar();
	if(pManager->getwin())
	{
		PlaySound("End.wav", NULL, SND_ASYNC);
		Sleep(1500);
	}
	else
	{
		PlaySound("fail.wav", NULL, SND_ASYNC);
		Sleep(2500);
	}
	outputFile.End(pManager);
}

StepAction::~StepAction()
{
}
