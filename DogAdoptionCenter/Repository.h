#pragma once
#include "DynamicVector.h"

// Repository module

template<typename T>
class Repository {
private:
	DynamicVector<T> arr;

public:

	// Constructor
	Repository();

	// Destructor
	~Repository();

	void add(T elem);
	T removeElem(int pos);
	T removeById(int id);
	T updateElem(int id, T newElem);
	T* getAllElements();
	T getElement(int pos);
	int getNrElements();
	bool existsElem(int id);
};

template<typename T>
Repository<T>::Repository()
{
}

template<typename T>
Repository<T>::~Repository()
{
}

template<typename T>
void Repository<T>::add(T elem)
{
	this->arr.add(elem);
}

template<typename T>
T Repository<T>::removeElem(int pos)
{
	return this->arr.removeElem(pos);
}

template<typename T>
inline T Repository<T>::removeById(int id)
{
	T* Elems = this->getAllElements();
	int nrElems = this->getNrElements();

	T elemTBR;

	for (int i = 0; i < nrElems; ++i)
		if (Elems[i].get_id() == id)
		{
			elemTBR = Elems[i];
			this->removeElem(i);
		}

	return elemTBR;
}

template<typename T>
T Repository<T>::updateElem(int id, T newElem)
{
	T* Elems = this->getAllElements();
	int nrElems = this->getNrElements();

	for(int i = 0; i < nrElems; ++i)
		if(Elems[i].get_id() == id)
			return this->arr.updateElem(i, newElem);
}

template<typename T>
T* Repository<T>::getAllElements()
{
	return this->arr.getAllElements();
}

template<typename T>
T Repository<T>::getElement(int pos)
{
	return this->arr.getElement(pos);
}

template<typename T>
inline int Repository<T>::getNrElements()
{
	return this->arr.getLength();
}

template<typename T>
inline bool Repository<T>::existsElem(int id)
{
	T* Elems = this->getAllElements();
	int nrElems = this->getNrElements();

	bool exists = false;

	for (int i = 0; i < nrElems; ++i)
		if (Elems[i].get_id() == id)
			exists = true;

	return exists;
}

