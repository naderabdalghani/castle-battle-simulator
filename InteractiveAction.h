#pragma once
#include "Action.h"
class InteractiveAction :
	public Action
{
	Point firstClick;
public:
	InteractiveAction(Battle *pApp);
	void Execute(GUI *&);
	~InteractiveAction();
};

