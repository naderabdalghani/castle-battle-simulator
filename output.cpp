#include "output.h"
#include"Battle.h"
output::output()
{
	outputFile.open("output.txt", ios::out);
	outputFile << "KTS\tS\tFD\tKD\tLT" << endl;
	FDsum = KDsum = 0;
	outputFile.close();
}

void output::Append(Battle *& GameBattle) {
	outputFile.open("output.txt", ios::app);
	node<Enemy*> *ptr;
	ptr = GameBattle->GetCastle()->gettowers()->getKilledQueue()->gethead();
	while (ptr != NULL) {
		outputFile << ptr->getvalue()->getKilledTimeStep() << "\t" << ptr->getvalue()->getID() << "\t" << ptr->getvalue()->getFirstShotDelay() << "\t" << ptr->getvalue()->getKilledDelay() << "\t" << ptr->getvalue()->getLifeTime() << endl;
		FDsum += ptr->getvalue()->getFirstShotDelay();
		KDsum += ptr->getvalue()->getKilledDelay();
		ptr = ptr->getnext();
	}
	GameBattle->GetCastle()->gettowers()->getKilledQueue()->clear();
	outputFile.close();
}

void output::End(Battle *& GameBattle) {
	outputFile.open("output.txt", ios::app);
	outputFile << "T1_Total_Damage\tT2_Total_Damage\tT3_Total_Damage\tT4_Total_Damage" << endl;
	Tower *T;
	T = GameBattle->GetCastle()->gettowers();
	for (int i = 0; i < 4; i++) {
		outputFile << T[i].GetHealth() << "\t";
	}
	outputFile << endl;
	outputFile << "R1_Unpaved_Dist\tR2_Unpaved_Dist\tR3_Unpaved_Dist\tR4_Unpaved_Dist" << endl;
	for (int i = 0; i < 4; i++) {
		outputFile <<  T[i].getPavedDistance() << "\t";
	}
	outputFile << endl;
	
	if (GameBattle->getwin() && GameBattle->getloss()) {
		outputFile << "The Game is a DRAW" << endl;
	}
	else {if (GameBattle->getwin()) { outputFile << "The Game is WON" << endl; }
	else {
		outputFile << "The Game is LOST" << endl;
		}
	}
	outputFile << "Total Enemies\t" << "= " << GameBattle->getEnemyCount() << endl;
	outputFile << "Average First-Shot Delay\t" << "= " << GameBattle->AverageFD() << endl;
	outputFile << "Average Kill Delay\t" << "= " << KDsum / GameBattle->getEnemyCount() << endl;
	outputFile.close();
}


output::~output()
{
}
