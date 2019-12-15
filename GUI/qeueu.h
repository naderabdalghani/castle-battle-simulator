#pragma once
#include<iostream>
using namespace std;
#include "node.cpp"

template <class T>
class qeueu
{
	node<T>* head, *tail;
	int count;
public:
	qeueu(void);
	~qeueu(void);

	int getcount();
	void enqueue(T val);
	void clear();
	bool dequeue();
	T front();
	T back();
	bool empty();

};

