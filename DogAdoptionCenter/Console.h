#pragma once
// Console module

#include "Service.h"
#include "Storage.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>

class Console {
private:
	Storage* st = nullptr;
	Service s;

public:

	Console();
	~Console();

	void printInitialPrompt();
	void printAdminMenu();
	void printUserMenu();
	void printAdoptionPrompt();
	void runConsole();
	void printFilePrompt();

	void writeDogsTXT();
	void readDogsTXT();

	void writeDogsHTML();
	void readDogsHTML();

	int read_integer();
};

Console::Console()
{
}

Console::~Console()
{
	if (this->st != nullptr)
		delete this->st;
}

void Console::printInitialPrompt()
{
	std::cout << "\nSelect the mode you would like to use the application in:"
		"\na - Administrator mode.\nu - User mode.\n";
}

void Console::printAdminMenu()
{
	std::cout << "\n1 - Add a dog.\n2 - Remove a dog.\n3 - Update a dog.\n4 - Print all dogs.\n5 - Exit.\n";
}

void Console::printUserMenu()
{
	std::cout << "\n1 - View dogs.\n2 - Filter dogs by breed, with maximum age.\n3 - See adoption list.\n4 - Display adoption list.\n5 - Exit\n";
}

inline void Console::printAdoptionPrompt()
{
	std::cout << "\n1 - Adopt.\n2 - See dog's photo.\n3 - Next.\n4 - See adoption list.\n5 - Display adoption list.\n6 - Return.\n";
}

inline void Console::runConsole()
{
	char initialCommand = 'l';
	int fileType = 0;

	while (fileType != 1 && fileType != 2)
	{
		try
		{
			this->printFilePrompt();
			fileType = this->read_integer();
		}
		catch (std::iostream::failure e)
		{
			std::cout << e.what() << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	while (true)
	{
		try
		{
			this->readDogsTXT();

			if (fileType == 2)
				this->st = new CSVStorage("Dogs.csv");
			else
				this->st = new HTMLStorage("Dogs.html");

			this->printInitialPrompt();

			std::cin >> initialCommand;

			if (initialCommand == 'a')
			{
				while (true)
				{
					this->printAdminMenu();

					int command;
					//std::cin >> command;
					command = this->read_integer();

					if (command == 1)
					{
						std::string name;
						std::string breed;
						int age;
						std::string photo_link;

						std::cout << "Name: ";
						std::cin >> name;
						std::cout << "Breed: ";
						std::cin >> breed;
						std::cout << "Age: ";
						//std::cin >> age;
						age = this->read_integer();
						std::cout << "Photo link: ";
						std::cin >> photo_link;

						this->s.addDogByVars(name, breed, age, photo_link);
					}
					else if (command == 2)
					{
						int id;
						std::cout << "The id of the dog to be removed: ";
						//std::cin >> id;
						id = this->read_integer();
						try
						{
							this->s.removeDogById(id);
						}
						catch (int ex)
						{
							if (ex == 21)
								std::cout << "The dog you are trying to remove does not exist.\n";
						}
					}
					else if (command == 3)
					{
						int id;
						std::string name;
						std::string breed;
						int age;
						std::string photo_link;

						std::cout << "The id of the dog you want to update: ";
						//std::cin >> id;
						id = this->read_integer();
						std::cout << "Name: ";
						std::cin >> name;
						std::cout << "Breed: ";
						std::cin >> breed;
						std::cout << "Age: ";
						//std::cin >> age;
						age = this->read_integer();
						std::cout << "Photo link: ";
						std::cin >> photo_link;

						try
						{
							this->s.updateDogById(id, name, breed, age, photo_link);
						}
						catch (int ex)
						{
							if (ex == 21)
								std::cout << "The dog you are trying to update does not exist.\n";
						}
					}
					else if (command == 4)
					{
						std::vector<Dog> dogs = this->s.getAllDogs();
						int nrDogs = this->s.getNrDogs();

						for (int i = 0; i < nrDogs; ++i)
							std::cout << dogs[i].ToString();
					}
					else if (command == 5)
					{
						this->writeDogsTXT();
						this->st->write_to_file(this->s);
						return;
					}
				}
			}
			else if (initialCommand == 'u')
			{
				while (true)
				{
					this->printUserMenu();
					int command;
					// std::cin >> command;
					command = this->read_integer();

					if (command == 1)
					{
						bool go = true;
						int ind = 0;
						int nrDogs = this->s.getNrDogs();
						std::vector<Dog> dogs = this->s.getAllDogs();
						int cmd;

						while (go && s.getNrDogs() != 0)
						{
							std::cout << "\nCurrent dog: " << dogs[ind % nrDogs].ToString() << "\n";
							this->printAdoptionPrompt();

							//std::cin >> cmd;
							cmd = this->read_integer();

							if (cmd == 1)
							{
								// Adding to adoption list.
								this->s.addToAdoptionList(dogs[ind % nrDogs]);

								// Removing from dog repo.
								this->s.removeDogById(dogs[ind % nrDogs].get_id());

								// Refresh dog list.
								dogs = this->s.getAllDogs();
								nrDogs = this->s.getNrDogs();
								//ind++;
							}
							else if (cmd == 2)
							{
								system(std::string("start " + dogs[ind % nrDogs].get_photoLink()).c_str());
							}
							else if (cmd == 3)
							{
								ind++;
							}
							else if (cmd == 4)
							{
								std::cout << "\nAdoption list: \n";

								std::vector<Dog> dogs = this->s.getAdoptedDogs();
								int nrDogs = this->s.getNrAdoptedDogs();

								for (int i = 0; i < nrDogs; ++i)
									std::cout << dogs[i].ToString();

								std::cout << '\n';
							}
							else if (cmd == 5)
							{
								this->st->write_to_file(this->s);
								system(std::string("start " + this->st->get_filename()).c_str());
							}
							else if (cmd == 6)
							{
								go = false;
							}
						}
					}
					else if (command == 2)
					{
						std::string breed;
						int age;
						std::getchar();
						std::cout << "The breed that you want to filter by: ";
						std::getline(std::cin, breed);
						std::istringstream iss(breed);
						std::cout << "The age that you want to filter by: ";
						// std::cin >> age;
						age = this->read_integer();

						std::vector<Dog> filteredDogs;

						filteredDogs = this->s.filterDogsBreedAge(breed, age);

						if (breed == "")
						{

							std::vector<Dog> dogs = this->s.getAllDogs();
							int nrDogs = this->s.getNrDogs();

							for (int i = 0; i < nrDogs; ++i)
								std::cout << dogs[i].ToString();
						}
						else
						{
							for (auto dog : filteredDogs)
								std::cout << dog.ToString();
						}
					}
					else if (command == 3)
					{
						std::vector<Dog> dogs = this->s.getAdoptedDogs();
						int nrDogs = this->s.getNrAdoptedDogs();

						std::cout << "\nAdoption list: \n";
						for (int i = 0; i < nrDogs; ++i)
							std::cout << dogs[i].ToString();
					}
					else if (command == 4)
					{
						this->st->write_to_file(this->s);
						system(std::string("start " + this->st->get_filename()).c_str());
					}
					else if (command == 5)
					{
						this->st->write_to_file(this->s);
						this->writeDogsTXT();
						return;
					}
				}
			}
		}
		catch (RepositoryException rex)
		{
			std::cout << rex.what() << '\n';
		}
		catch (ValidationException vex)
		{
			std::cout << vex.what() << '\n';
		}
		catch (std::iostream::failure e)
		{
			std::cout << e.what() << '\n';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

inline void Console::printFilePrompt()
{
	std::cout << "Select the type of file you want to read from and store changes in:\n"
		"1 - HTML\n2 - CSV\n";
}

inline void Console::writeDogsTXT()
{
	std::ofstream fout("Dogs.txt", std::ofstream::trunc);

	if (!fout.is_open())
		return;

	std::vector<Dog> dogs = this->s.getAllDogs();

	for (auto dog : dogs)
		fout << dog;

	fout.close();
}

inline void Console::readDogsTXT()
{
	std::ifstream fin("Dogs.txt");

	if (!fin.is_open())
		return;

	Dog d;
	while (fin >> d)
	{
		this->s.addDog(d);
		d.incrementId();
	}

	fin.close();
}

inline void Console::writeDogsHTML()
{
}

inline void Console::readDogsHTML()
{
}

inline int Console::read_integer()
{
	int x;

	if (std::cin >> x) {
		return x;
	}
	else {
		throw std::iostream::failure("Bad input!");
	}
}
