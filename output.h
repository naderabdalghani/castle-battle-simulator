#pragma once

#include<fstream>
#include <iostream>
using namespace std;
class Battle;
class output
{
	ofstream outputFile;
	int FDsum, KDsum;
public:
	output();
	void Append(Battle *& );
	void End(Battle *& );
	~output();
};

