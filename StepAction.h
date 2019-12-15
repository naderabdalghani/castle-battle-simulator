#pragma once
#include "Action.h"
class StepAction :
	public Action
{
public:
	StepAction(Battle *pApp);
	void Execute(GUI*&);
	void wait(int seconds);
	~StepAction();
};

