#pragma once
#include "Action.h"
class SilentAction :
	public Action
{
public:
	SilentAction(Battle *pApp);
	void Execute(GUI*&);
	~SilentAction();
};

