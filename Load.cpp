#include "Load.h"


Load::Load() 
{}
Load:: ~Load() {

}
void Load::ReadActionParameters(GUI* pOut)
{   
	pOut->PrintMessage("enter the file name");

    fileName = pOut->GetString();
	InFile.open(fileName,ios::in);
	while (!(InFile.is_open()))//check if the file opens or not if not it keeps asking for a valid name.
	{   pOut->ClearStatusBar();
		pOut->PrintMessage("please enter valid file name");
		fileName = pOut->GetString();
		InFile.open(fileName, ios::in);
	}
		

}
void Load::Execute(GUI *& Out,Battle* &GameBattle)
{
	ReadActionParameters(Out);
	int th, n,tp;
	InFile >> th>>n>>tp;
	Tower T (th,n,tp);
	GameBattle->GetCastle()->SetTowersinfo(T);
	float c1,c2,c3;
	InFile >> c1>>c2>>c3;
	Shielded::setConst(c1,c2,c3);
	int s,typ,t,h,pow,sp,rld;
	char reg;
	InFile>>s;
	REGION r=A_REG;
	while (s!=-1)//as we don't reach end of file continue working
	{
		InFile>>typ>>t>>h>>pow>>rld>>sp>>reg;
	switch (reg)
	{ case ('A'):
			 r = A_REG;  	
			break;
	case ('B'):
			 r = B_REG;  	
			break;
	case ('C'):
		     r = C_REG;  	
			break;
	case ('D'):
			 r = D_REG;  	
			break;
	default:
		break;
	}
	
		if (typ == 0)
		{
			Enemy* e =new Paver(s,t,h,pow,rld,sp,r);
			GameBattle->AddEnemy(e);
		}
		else if (typ == 1)
		{
		Enemy* e =new Fighter(s,t,h,pow,rld,sp,r);
			GameBattle->AddEnemy(e);
		}
		else  
		{
			Enemy* e =new Shielded(s,t,h,pow,rld,sp,r);
			GameBattle->AddEnemy(e);
		
		}
		
		InFile>>s;
	}
	InFile.close();
	return;
}
