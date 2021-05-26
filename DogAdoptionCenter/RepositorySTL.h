#pragma once
#include <vector>
#include <algorithm>
#include "RepositoryException.h"
// STL vector based Repository module

template<typename T>
class STLRepository {
private:
	std::vector<T> vector;

public:
	// Constructor.
	STLRepository();

	// Destructor.
	~STLRepository();

	// Add an element.
	void add(T elem);

	// Remove element by position.
	T removeElem(int pos);

	// Remove element by id.
	T removeById(int id);

	// Update an element by id.
	T updateElem(int id, T newElem);

	// Get all elements.
	typename std::vector<T> getAllElements();

	// Get element by position.
	T getElement(int pos);

	// Get the number of total elements.
	int getNrElements();

	// Check if element exists by id.
	bool existsElem(int id);

    // Get element by id.
    T getElementId(int id);
};

template<typename T>
inline STLRepository<T>::STLRepository()
{
}

template<typename T>
inline STLRepository<T>::~STLRepository()
{
}

template<typename T>
inline void STLRepository<T>::add(T elem)
{
	this->vector.push_back(elem);
}

template<typename T>
inline T STLRepository<T>::removeElem(int pos)
{
	T elemTBR;
	try
	{ 
		elemTBR = this->vector.at(pos);
		this->vector.erase(this->vector.begin() + pos);
	}
    catch (const std::exception& oor)
	{
		throw oor;
	}

	return elemTBR;
}

template<typename T>
inline T STLRepository<T>::removeById(int id)
{
	if (!this->existsElem(id))
		throw RepositoryException("The element that you want to remove does not exist!");

	T elemTBR;

	for(unsigned int i = 0; i < this->vector.size(); ++i)
		if (this->vector[i].get_id() == id)
		{
			elemTBR = this->vector[i];
			this->removeElem(i);
			break;
		}

	return elemTBR;
}

template<typename T>
inline T STLRepository<T>::updateElem(int id, T newElem)
{
	if (!this->existsElem(id))
		throw RepositoryException("The element that you want to update does not exist!");

	T elemTBR;

	for(auto& elem : this->vector)
		if (elem.get_id() == id)
		{
			elemTBR = elem;
			newElem.set_id(elem.get_id());
			elem = newElem;
		}

	return elemTBR;
}

template<typename T>
inline typename std::vector<T> STLRepository<T>::getAllElements()
{
	return this->vector;
}

template<typename T>
inline T STLRepository<T>::getElement(int pos)
{
	return this->vector[pos];
}

template<typename T>
inline int STLRepository<T>::getNrElements()
{
	return this->vector.size();
}

template<typename T>
inline bool STLRepository<T>::existsElem(int id)
{
	for (auto elem : this->vector)
		if (elem.get_id() == id)
			return true;

	return false;
}

template<typename T>
inline T STLRepository<T>::getElementId(int id)
{
    for(auto elem : this->vector)
        if(elem.get_id() == id)
            return elem;
}
