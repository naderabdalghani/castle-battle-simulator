#include "SilentAction.h"
#include "Battle.h"


SilentAction::SilentAction(Battle *pApp) : Action(pApp)
{
}

void SilentAction::Execute(GUI*& a) {
	bool flag = true;
	int time=0;
	while (flag) {
		flag = pManager->SilentBattleSimulation(time);
		outputFile.Append(pManager);
		time++;
	}
	a->ClearStatusBar();
	a->DrawBackground();
	a->DrawCastle();
	outputFile.End(pManager);
	if(pManager->getwin())
	{
		PlaySound("End.wav", NULL, SND_ASYNC);
		Sleep(1500);
	}
	else
	{
		PlaySound("fail.wav", NULL, SND_ASYNC);
		Sleep(1500);
	}
}

SilentAction::~SilentAction()
{
}
