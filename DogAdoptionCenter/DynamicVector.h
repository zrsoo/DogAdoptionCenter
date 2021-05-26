// DynamicVector module
#include <assert.h>
#include <iostream>
#pragma once

template<typename T>
class DynamicVector {
private:
	T* arr;
	int nrElem;
	int capacity;

public:
	// Constructor of DynamicVector
	DynamicVector(int capacity = 10);

	// Copy constructor of DynamicVector
	DynamicVector(const DynamicVector& v);

	// Destructor
	~DynamicVector();

	/*
		Overloading the subscript operator
		Input: pos - a valid position within the vector.
		Output: a reference to the element o position pos.
	*/
	T& operator[](int pos);

	// Adds an element to the current Dynamic Vector.
	void add(T elem);

	// Returns the current length of the Dynamic Vector.
	int getLength() const;

	// Removes the element from a specified position. Returns the removed element.
	T removeElem(int pos);

	// Updates the element on a specific position. Returns the old element.
	T updateElem(int pos, T newElem);

	// Gets the element from a specified position in the array.
	T& getElement(int pos);

	// Gets all elements.
	T* getAllElements();

private:
	// Resizes the array, doubling the capacity.
	void resize();
};

template<typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	assert(capacity >= 0);

	this->nrElem = 0;
	this->capacity = capacity;
	this->arr = new T[capacity];
}

template<typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& v)
{
	// Copy constructor - TBI
}

template<typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->arr;
}

template<typename T>
T& DynamicVector<T>::operator[](int pos)
{
	return getElement(pos);
}

template<typename T>
void DynamicVector<T>::add(T elem)
{
	// First, check if there is any room for the element to be added.
	// If there isn't resize the array, doubling the capacity.
	if (this->nrElem == this->capacity - 1)
		resize();

	// Then, add the element to the end.
	this->arr[this->nrElem] = elem;
	this->nrElem++;
}

template<typename T>
inline int DynamicVector<T>::getLength() const
{
	return this->nrElem;
}

template<typename T>
inline T DynamicVector<T>::removeElem(int pos)
{
	// If the element is on the last position, simply decrement the number of elements.
	if (pos == this->nrElem - 1)
	{
		this->nrElem--;
		return this->arr[pos];
	}
	// Else, shift all the elements succeeding the element to be removed one position to the left.
	else
	{
		T element = this->arr[pos];
		for (int i = pos; i < this->nrElem - 1; ++i)
			this->arr[i] = this->arr[i + 1];
		this->nrElem--;
		return element;
	}
}

template<typename T>
inline T DynamicVector<T>::updateElem(int pos, T newElem)
{
	T elemTBR = this->arr[pos];
	newElem.set_id(elemTBR.get_id());
	this->arr[pos] = newElem;

	return elemTBR;
}

template<typename T>
void DynamicVector<T>::resize()
{
	// Allocating new, bigger array.
	this->capacity = this->capacity * 2;
	T* newarr = new T[this->capacity];

	// Copying elements into the bigger array
	for (int i = 0; i < this->nrElem; ++i)
		newarr[i] = this->arr[i];

	// Deallocating old array.
	delete[] this->arr;

	// Pointing to new array.
	this->arr = newarr;
}

template<typename T>
T& DynamicVector<T>::getElement(int pos)
{
	if (pos >= this->nrElem)
		throw 20;

	return this->arr[pos];
}

template<typename T>
inline T* DynamicVector<T>::getAllElements()
{
	return this->arr;
}
