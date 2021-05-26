// Dog module
#include <string>
#include <iostream>
#pragma once

class Dog
{
private:
	static int current_id;
	int id;
	std::string name;
	std::string breed;
	int age;
	std::string photo_link;

public:

	// Default constructor of a dog.
	Dog();

	// Constructor of a dog.
	Dog(std::string name, std::string breed, int age, std::string photo_link);

	// Destructor of a dog.
	~Dog();

	// ToString method.
	std::string ToString() const;

	// Id getter
	int get_id();

	// Name getter
	std::string get_name();

	// Breed getter
	std::string get_breed();

	// Age getter
	int get_age();

	// Photo link getter
	std::string get_photoLink();

	// Id setter
	void set_id(int id);

	// Overloading "<<" operator.
	friend std::ostream& operator<<(std::ostream& os, const Dog& d);

	// Overloading ">>" operator.
	friend std::istream& operator>>(std::istream& is, Dog& d);

	// Increment id.
	void incrementId();

	// Return nice string for HTML printing
	std::string ToHTML();
};