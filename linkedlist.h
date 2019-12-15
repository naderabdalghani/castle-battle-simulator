#pragma once
#include<iostream>
using namespace std;
#include "node.h"

template <class T>
class linkedlist
{
	node<T>* head,*tail;
	int count;
	node<T>* SortedMerge(node<T>* a, node<T>* b);
	void FrontBackSplit(node<T>* source,node<T>** frontRef, node<T>** backRef);
	void MergeSort(node<T>** headRef);
	
public:
	linkedlist();
	bool isempty();	
	int getcount();
	void add(T val);
	void clear();
	void Sort();
	node<T>* gethead();
	~linkedlist();
	bool remove(T data);//////////////////////////added
};

template <class T>
bool linkedlist<T>::remove(T data)////////////////////////added
{
	
	if(!head)
		return false;
	node<T>* ptr= head;
	if (data ==head->getvalue())
	{
		head=head->getnext();
		delete ptr;
		return true;
	}
	
	while( ptr->getnext()!= NULL && ptr->getnext()->getvalue() != data )
		ptr=ptr->getnext();
	if(ptr->getnext()== NULL)
		return false;
	node<T>*temp=ptr->getnext();
	ptr->setnext(temp->getnext());
	delete temp;
	return true;
}



template <class T>
bool linkedlist<T>::isempty()
{
	return (getcount()==0 );
}

template <class T>
int linkedlist<T>::getcount()
{
	return count;
}

template <class T>
void linkedlist<T>::add(T val)
{
	node<T>*  inserted=new node<T>(val);
	if(!head){
		head=tail=inserted;
		tail->setnext(NULL);
		count++;}
	else 
	{
		tail->setnext(inserted);
		tail=tail->getnext();
		tail->setnext(NULL);
	     count++;
	}
	
}
template <class T>
void linkedlist<T>::clear()
{
	while(head)
	{
		node<T>* ptr= head;
		head=head->getnext();
		delete ptr;
	}
	tail=NULL;
	count=0;

}

template <class T>
linkedlist<T>::linkedlist()
{
	head=NULL;
	tail=NULL;
	count=0;
}

template <class T>
node <T>* linkedlist<T>::gethead()
{   node<T>* temp=head;
	return temp;
}


template <class T>
linkedlist<T>::~linkedlist()
{
		clear();
	
}
template <class T>
void linkedlist<T>::FrontBackSplit(node<T>* source,node<T>** frontRef, node<T>** backRef)
{
    node<T>* fast;
    node<T>* slow;
    slow = source;
    fast = source->getnext();
 
    while (fast != NULL)
    {
		fast = fast->getnext();
		if (fast != NULL)
		{
			slow = slow->getnext();
			fast = fast->getnext();
		}
    }
 
    *frontRef = source;
    *backRef = slow->getnext();
    slow->setnext (NULL);
}
template <class T>
void linkedlist<T>::MergeSort(node<T>** headRef)
{
	node<T>* head = *headRef;
	node<T>* a;
	node<T>* b;
 
if ((head == NULL) || (head->getnext() == NULL))
{
    return;
}
 
/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b); 
 
/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);
 
/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}
template <class T> 
node<T>* linkedlist<T>::SortedMerge(node<T>* a, node<T>* b)
{
	node<T>* result = NULL;
 
/* Base cases */
	if (a == NULL)
		 return b;
	else if (b==NULL)
		 return a;
 
/* Pick either a or b, and recur */
	if (a->getvalue() <= b->getvalue())
	{
		result = a;
		result->setnext (SortedMerge(a->getnext(), b));
	}
	else
	{
		result = b;
		result->setnext (SortedMerge(a, b->getnext()));
	}

	return result;
}
template<class T>
void linkedlist<T>:: Sort(){
	MergeSort(&head);
	node<T>* ptr = head;   // set correct tail for new addition
	if ((head == NULL) || (head->getnext() == NULL))
	{
		
		return;
	}
	while (ptr->getnext())
	{
		ptr=ptr->getnext();
	}
	tail=ptr;
}