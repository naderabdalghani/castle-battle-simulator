#include "InteractiveAction.h"
#include "Input.h"
#include "Battle.h"

InteractiveAction::InteractiveAction(Battle *pApp) : Action(pApp)
{
	firstClick.x = 0;
	firstClick.y = 0;
}

void InteractiveAction::Execute(GUI *& pGUI) 
{
	Input *pIn = pManager->GetInput();
	bool flag = true;
	int time=0;
	while (flag)
	{
		flag = pManager->BattleSimulation(pGUI,time);
		outputFile.Append(pManager);
		time++;
		pIn->GetPointClicked(firstClick.x, firstClick.y);
	}
	pManager->drawPaveddis(pManager->GetCastle()->gettowers(),pGUI);
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

InteractiveAction::~InteractiveAction()
{
}
