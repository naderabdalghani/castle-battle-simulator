#pragma once
#include<iostream>
using namespace std;

template <class T>
class node
{
	T data;
	node* next;
public:
	node();
	node(T value);
	void setvalue(T val);
	void setnext(node<T>*);
	T getvalue ();
	node<T>* getnext();
	~node();
};

template <class T>
node<T>::node(T value)
{
	next=NULL;
	data=value;
}

template <class T>
node<T>::node()
{
	setnext(NULL);
}

template<class T>
void node<T>::setvalue(T val)
{
	data=value;
}

template<class T>
void node<T>::setnext(node<T>* nex)
{
	next=nex;
}

template<class T>
T node<T>::getvalue ()
{
	return data;
}

template<class T>
node<T>* node<T>::getnext()
{
	return next;
}

template <class T>
node<T>::~node()
{}

