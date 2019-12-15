#ifndef ACTION_H
#define ACTION_H

#include "Defs.h"
#include "output.h"
#include "GUI\GUI.h"

class Battle; //forward class declaration


			  //Base class for all possible actions
class Action 
{
protected:
	output outputFile;
	Battle * pManager;	//Actions needs AppMngr to do their job
public:

	Action(Battle *&pApp); 	//constructor


	//Execute action (code depends on action type)
	virtual void Execute(GUI*&) = 0;

};


#endif