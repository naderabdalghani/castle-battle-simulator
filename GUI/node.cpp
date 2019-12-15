#include<iostream>
using namespace std;
#include "node.h"
template <class T>
node<T>::node(T value)
{
	next=NULL;
	data=value;
}

template <class T>
node<T>::node()
{
	next(NULL)
}

template<class T>
void node<T>::setvalue(T val)
{
	setvalue(val);
}

template<class T>
void node<T>::setnext(node<T>* nex)
{
	next=nex;
}
template<class T>

T node<T>::getvalue ()
{
	return value;
}

template<class T>
node<T>* node<T>::getnext()
{
	return next;
}

template <class T>
node<T>::~node()
{
}
