#include<fstream>
#include <iostream>
using namespace std;
#include "GUI\GUI.h"
#include "Battle.h"
#pragma once

class Load 
{ private:
	ifstream InFile;
	string fileName;
public:
	Load();
	void ReadActionParameters(GUI* p);
	void Execute(GUI* &,Battle*&);
	~Load();
};