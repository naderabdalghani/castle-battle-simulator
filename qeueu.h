#pragma once
#include<iostream>
using namespace std;
#include "node.h"

template <class T>
class qeueu
{
	node<T>* head, *tail;
	int count;
public:
	qeueu(void);
	int getcount() ;
	void enqueue(T val);
	void clear();
	bool dequeue();
	T front();
	T back();
	bool empty();
	node<T>* gethead();
	~qeueu(void);
};


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
void qeueu<T>::enqueue(T val) 
{
	node<T>* inserted =new node<T> (val);
	if(!tail)
	{
		
		tail=head=inserted;
	}
	else if(inserted ->getvalue() > front())
	{
		inserted->setnext(head);
		head=inserted;
	}
	else if(inserted ->getvalue() < back())
	{
		tail->setnext(inserted);
		tail=inserted;
	}
	else
	{
		node<T>* ptr=head->getnext();
		node<T>* prev=head;
		while(ptr > inserted)
		{
			ptr=ptr->getnext();
			prev=prev->getnext();
		}
		inserted->setnext(ptr);
		prev->setnext(inserted);
	}
count++;
}


/*template <class T>
void qeueu<T>::enqueue(T val) // add element at the end of the list
{
	if(!tail)
	{
		node<T>* inserted =new node<T> (val);
		tail=head=inserted;
		count++;
	}
	else
	{
		node<T>* inserted =new node<T> (val);
		tail->setnext(inserted);
		tail= inserted;
		tail->setnext(NULL);
		count++;
	}
}
*/	

template <class T>
void qeueu<T>::clear()
{
	while(head)
		dequeue();
	head=tail=NULL;
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
		delete del; //// et3dlt 
		count--;
		return true;
	}
	else
	{
		node<T>* del=head;
		head=head->getnext();
		delete del;
		count--;
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
template <class T>
node<T>* qeueu<T>::gethead(){
	node<T>* temp=head;
	return temp;
}