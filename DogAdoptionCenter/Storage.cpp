#include "Storage.h"
#include <fstream>
#include <vector>
#pragma once
// Implementation of Storage classes

Storage::Storage(std::string filename) : _filename{filename}
{
}

Storage::~Storage()
{
}

std::string Storage::get_filename() const
{
	return this->_filename;
}

CSVStorage::CSVStorage(std::string filename) : Storage{ filename }
{
}

CSVStorage::~CSVStorage()
{
}

void CSVStorage::write_to_file(Service s) const
{
	std::ofstream fout(this->_filename, std::ofstream::trunc);

	if (!fout.is_open())
		return;

	std::vector<Dog> dogs = s.getAdoptedDogs();

	for (auto dog : dogs)
		fout << dog;

	fout.close();
}

void CSVStorage::open_file() const
{
    system(std::string("start " + this->get_filename()).c_str());
}

HTMLStorage::HTMLStorage(std::string filename) : Storage{ filename }
{
}

HTMLStorage::~HTMLStorage()
{
}

void HTMLStorage::write_to_file(Service s) const
{
	std::ofstream fout(this->_filename, std::ofstream::trunc);

	if (!fout.is_open())
		return;

	std::vector<Dog> dogs = s.getAdoptedDogs();

	fout << "<!DOCTYPE html>    <!-- write this exactly as it is here -->\n"
		"<html> <!--write this exactly as it is here-->\n"
		"<head> <!--write this exactly as it is here-->\n"
		"<title>Adoption list</title> <!--replace “Playlist” with the title for your HTML-->\n"
		"</head> <!--write this exactly as it is here(close head tag)-->\n"
		"<body> <!--write this exactly as it is here-->\n"
		"<table border = \"1\"> <!--write this exactly as it is here-->\n";

	fout << "<tr> <!--tr = table row; 1 row for each entity-->\n"
		"<td>Id</td> <!--td = table data; 1 td for each attribute of the entity-->\n"
		"<td><b>Name</b></td>\n"
		"<td><b>Breed</b></td>\n"
		"<td><b>Age</b></td>\n"
		"<td><b>Photo link</b></td>\n"
		"</tr>\n";

	for (auto dog : dogs)
		fout << dog.ToHTML();

	fout << "</table>\n"
		"</body>\n"
		"</html>\n";

	fout.close();
}

void HTMLStorage::open_file() const
{
    system(std::string("start " + this->get_filename()).c_str());
}
