#include "qeueu.h"
#include<iostream>
using namespace std;

template <class T>
qeueu<T>::qeueu(void)
{
	head=NULL;
	tail=NULL;
	count=0;
}

template <class T>
qeueu<T>::~qeueu(void)
{
	while(!empty())
		clear();
}

template <class T>
int qeueu<T>::getcount()
{
	return count;
}

template <class T>
void qeueu<T>::enqueue(T val) // add element at the end of the list
{
	if(!tail)
	{
		node<T>* inserted =new node<T> (val);
		tail=head=inserted;
	}
	else
	{
		node<T>* inserted =new node<T> (val);
		tail->setnext()=inserted;
		tail= inserted;
		count++;
	}
}
	

template <class T>
void qeueu<T>::clear()
{
	while(head)
		dequeue();
}

template <class T>
bool qeueu<T>::dequeue()
{
	if (empty())
		return false;
	if(count==1)
	{
		node<T>* del=head;
		head=tail=NULL;
		delete det;
		count--;
		return true;
	}
	else
	{
		node<T>* del=head;
		head=head->getnext();
		delete del;
		count--;
		if (empty())
			tail =NULL;
		return true;
	}
	
}

template <class T>
T qeueu<T>::front()
{
	return head->getvalue();
}

template <class T>
T qeueu<T>::back()
{
	return tail->getvalue();
}

template <class T>
bool qeueu<T>::empty()
{
	return (getcount()==0);
}