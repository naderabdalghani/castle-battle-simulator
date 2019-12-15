#pragma once
#include<iostream>
using namespace std;

template <class T>
class node
{
	T data;
	node* next;
public:
	void setvalue(T val);
	void setnext(node<T>* nex);
	T getvalue ();
	node<T>* getnext();
	node();
	node(T value);
	~node();
};
