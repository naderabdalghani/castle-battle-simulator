#include "Battle.h"
#include "Load.h"
//#include<mmsystem.h>
//#include<mciapi.h>
//PlaySound("shot.wav", NULL, SND_ASYNC);
int main()
{
	GUI * pGUI = new GUI;
	Battle* pGameBattle = new Battle(pGUI);
	Load* l;
	l = NULL;
	ActionType ActType;
	bool GameStarted = false;
	do
	{
		//Read user action
		ActType = pGameBattle->GetUserAction();
		if (ActType == 0) {
			GameStarted = true;
			l = new Load();
			pGUI->ClearStatusBar();
			l->Execute(pGUI, pGameBattle);
			pGUI->ClearStatusBar();
		}
		//Exexute the action
		else {
			if (l != NULL && ActType != MENU_EXIT) {
				while (pGameBattle->GetUserAction() != MENU_EXIT) {
					pGameBattle->ExecuteAction(pGUI, ActType);
					pGUI->PrintMessage("The Game has Ended");
				}
			}
			else {
				if (ActType != MENU_EXIT) {
					pGUI->PrintMessage("Please load a file first!");
				}
			}

		}

	} while (ActType != MENU_EXIT);

	if (GameStarted) {
		delete pGameBattle;
		delete l;
		delete pGUI;
		return 0;
	}
}
