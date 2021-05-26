#include "Dog.h"
#include <sstream>
#include <iostream>
#include <vector>


Dog::Dog()
{
	this->id = this->current_id;
	this->name = "";
	this->breed = "";
	this->age = 0;
	this->photo_link = "";

	this->current_id++;
}

Dog::Dog(std::string _name, std::string _breed, int _age, std::string _photo_link) : name{ _name }, breed{ _breed }, age{ _age }, photo_link{ _photo_link }
{
	this->id = this->current_id;
	this->current_id++;
}

Dog::~Dog()
{
}

std::string Dog::ToString() const
{
	std::stringstream buffer;
	buffer << "Id: " << this->id << "; Name: " << this->name << "; Breed: " << this->breed << "; Age: " << this->age << "; Photo: " << this->photo_link << " \n";
	return buffer.str();
}

int Dog::get_id()
{
	return this->id;
}

std::string Dog::get_name()
{
	return this->name;
}

std::string Dog::get_breed()
{
	return this->breed;
}

int Dog::get_age()
{
	return this->age;
}

std::string Dog::get_photoLink()
{
	return this->photo_link;
}

void Dog::set_id(int id)
{
	this->id = id;
}

void Dog::incrementId()
{
	this->current_id++;
}

std::string Dog::ToHTML()
{
	std::stringstream buffer;
	buffer << "<tr>\n" << "<td>" << this->id << "</td>\n" << "<td>" << this->name << "</td>\n" << "<td>" << this->breed << "</td>\n" << "<td>" << this->age << "</td>\n" << "<td>" << "<a href=\"" << this->photo_link << "\">Link</a>" << "</td>\n" << "</tr>\n";
	return buffer.str();
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector<std::string>result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

int string_to_int(std::string s)
{
	std::stringstream ss(s);

	int x = 0;
	ss >> x;

	return x;
}

std::ostream& operator<<(std::ostream& os, const Dog& d)
{
	os << d.id << "," << d.name << "," << d.breed << "," << d.age << "," << d.photo_link << " \n";
	return os;
}

std::istream& operator>>(std::istream& is, Dog& d)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = tokenize(line, ',');

	if (tokens.size() != 5)
		return is;

	d.id = string_to_int(tokens[0]);
	d.name = tokens[1];
	d.breed = tokens[2];
	d.age = string_to_int(tokens[3]);
	d.photo_link = tokens[4];

	return is;
}


int Dog::current_id = 0;