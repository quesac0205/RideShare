#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "defs.h"

using namespace std;

// templating the List.h/List.cc class
template <typename T>

class List
{

public:
	// constructor with compare function pointer
	List(int (*compare)(T t1, T t2));

	// destructor
	~List();

	// other
	void add(T t);			// change
	T remove(int index);	// change
	T get(int index) const; // change
	int getSize() const;
	bool isFull() const;
	void clear(); // delete elements

private:
	int numElements;			// num of total elements
	T *elements;				// pointer to T elements array
	int (*compare)(T t1, T t2); // compare function pointer
};

template <typename T>
List<T>::List(int (*compare)(T t1, T t2)) : compare(compare) // generic constructor
{
	elements = new T[MAX_ARRAY];
	numElements = 0;
}
template <typename T>
List<T>::~List()
{
	delete[] elements;
}

template <typename T>
void List<T>::add(T t)
{
	if (numElements >= MAX_ARRAY)
	{
		cerr << "List is full" << endl;
		exit(1);
	}
	int i = numElements - 1;
	while (i >= 0 && compare(elements[i], t) > 0)
	{
		elements[i + 1] = elements[i]; // make space of the new element by shifting right
		--i;
	}
	elements[i + 1] = t; // add the element
	++numElements;
}
template <typename T>
T List<T>::remove(int index)
{
	if (index < 0 || index >= numElements)
	{
		cerr << "Index Out of bound error!" << endl;
		exit(1);
	}

	T temp = elements[index];

	while (index < numElements)
	{
		elements[index] = elements[index + 1]; // move the element to left
		++index;
	}
	--numElements;
	return temp;
}
template <typename T>
int List<T>::getSize() const
{
	return numElements;
}
template <typename T>
bool List<T>::isFull() const
{
	return numElements >= MAX_ARRAY;
}
template <typename T>
T List<T>::get(int index) const
{
	if (index < 0 || index >= numElements)
	{
		cerr << "List index out of bounds" << endl;
		exit(1);
	}
	return elements[index];
}

template <typename T>
void List<T>::clear()
{
	numElements = 0;
}
#endif