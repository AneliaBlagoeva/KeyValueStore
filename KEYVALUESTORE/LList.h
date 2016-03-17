#ifndef _LLIST_H_
#define _LLIST_H_

#include<iostream>
using namespace std;

template<class T>
struct elem
{
	T content;
	elem * link;

	elem()
	{
		content = T();
		link = NULL;
	}

	elem(T x)
	{
		content = x;
		link = NULL;
	}

};

template<class T>
class LList
{
private:
	elem<T> * start;
	elem<T> * end;
	void copy(const LList<T> & ob);
public:
	void free();
	LList();
	~LList();
	LList(const LList<T> &);
	LList<T> & operator=(const LList<T>&);

	elem<T>* Iter(elem<T>*);
	void print()const;
	void insertBack(T);
	void insertFront(T);
	void deleteElem(int);

	int getSize()const;
	elem<T>* getStart()const;
	elem<T>* getEnd()const;
	bool isEmpty()const;

};
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
void LList<T>::free()
{
	elem<T> *current = start;
	if (end != NULL)//if list is not empty
	{
		while (current)
		{
			elem<T> * p = current;
			current = current->link;
			delete p;
		}
	   end = NULL;
	   start = NULL;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
elem<T>* LList<T>::Iter(elem<T>*p)
{
	p = p->link;
	return p;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
void LList<T>::copy(const LList<T>& ob)
{
	elem<T> * current = new (nothrow)elem < T > ;//current element of new list
	if (current == NULL && ob.getStart()==NULL)
	{
		cout << "Error!" << endl;
		return;
	}

	current->content=ob.start->content;//get content of object.start
	end = start = current;

	elem<T> * temp = ob.start;//iterating element of object
	if (current != NULL)
	{
		while (temp->link != NULL)
		{
			current->link = new (nothrow)elem < T > ;//create new node for our next
			current = current->link;//come in our new element
			
			temp = temp->link;//get next element from object

			current->content = temp->content;
			
			end = current;
			end->link = NULL;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
LList<T>::LList()
{
	start = NULL;
	end = NULL;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
LList<T>::~LList()
{
	free();
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
LList<T>::LList(const LList<T>& r)
{
	copy(r);
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
LList<T>& LList<T> :: operator=(const LList<T>& r)
{
	if (this != &r)
	{
		free();
		copy(r);
	}
	return *this;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
void LList<T>::print()const
{
	elem<T> * p = new (nothrow)elem<T>;
	if (p == NULL)
	{
		cout << "Error: memory could not be allocated";
	}

	p = start;

	while (p != NULL)
	{
		cout << p->content << " " << endl;
		p = p->link;
	}
	delete p;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
void LList<T>::insertBack(T x)
{

	elem<T> * temp = new (nothrow)elem<T>;//create new element
	if (temp == NULL)
	{
		cout << "Error: memory could not be allocated";
	}
	temp->content = x;//set content of our element
	temp->link = NULL;//set link of our element

	if (NULL == start && NULL == end) // empty list
	{
		start = end = temp;
	}
	else if (start == end) // list with one elem
	{
		end = temp;
		start->link = temp;
	}
	else  // with more elements
	{
		end->link = temp;
		end = temp;
	}

}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
void LList<T>::insertFront(T x)
{
	elem<T>* temp = new (nothrow)elem < T >;
	if (temp == NULL)
	{
		cout << "Error: memory could not be allocated";
	}

	//set new element before start
	temp->content = x;
	temp->link = start;
	start = temp;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
int LList<T>::getSize()const
{
	int cnt = 0;
	elem<T> * p = new (nothrow)elem < T >;
	if (p == NULL)
	{
		cout << "Error: memory could not be allocated";
		return 1;
	}
	p = start;

	while (p != NULL)
	{
		p = p->link;
		cnt++;
	}

	delete p;
	return cnt;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
void LList<T>::deleteElem(int index)
{
	elem<T>* q = start;
	int i = 1;
	while (i <index - 1)
	{
		q = Iter(q);
		i++;
	}
	q->link = (q->link)->link;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
elem<T> * LList<T>::getStart()const
{
	return start;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
elem<T> * LList<T>::getEnd()const
{
	return end;
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class T>
bool LList<T>::isEmpty()const
{
	return (start==NULL || end == NULL);
}

#endif