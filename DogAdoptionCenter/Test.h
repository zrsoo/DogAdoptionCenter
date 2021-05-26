// Test module
#pragma once
#include "Service.h"
#include "RepositoryException.h"

class Test {
private:
	Service s_test;

public:

	void test_add();
	void test_remove();
	void test_update();

	void run_tests();
};

void Test::test_add()
{
	int nrDogs = this->s_test.getNrDogs();

	this->s_test.addDogByVars("Bobita", "Yorkshire Terrier", 11, "https://www.pexels.com/photo/two-yellow-labrador-retriever-puppies-1108099/");

	int newNrDogs = this->s_test.getNrDogs();

	assert(nrDogs == newNrDogs - 1);

	this->s_test.addDogByVars("Rex", "German Shepherd", 2, "https://www.pexels.com/photo/brown-and-white-short-coated-puppy-1805164/");

	std::vector<Dog> dogs = this->s_test.getAllDogs();
	
	assert(dogs[0].get_name() == "Bobita");
	assert(dogs[0].get_breed() == "Yorkshire Terrier");
	assert(dogs[0].get_age() == 11);
	assert(dogs[0].get_photoLink() == "https://www.pexels.com/photo/two-yellow-labrador-retriever-puppies-1108099/");

	assert(dogs[1].get_name() == "Rex");
	assert(dogs[1].get_breed() == "German Shepherd");
	assert(dogs[1].get_age() == 2);
	assert(dogs[1].get_photoLink() == "https://www.pexels.com/photo/brown-and-white-short-coated-puppy-1805164/");
}

void Test::test_remove()
{
	int nrDogs = this->s_test.getNrDogs();

	std::vector<Dog> dogs = this->s_test.getAllDogs();

	this->s_test.removeDogById(dogs[0].get_id());

	int newnrDogs = this->s_test.getNrDogs();

	assert(newnrDogs == nrDogs - 1);

	this->s_test.removeDogById(dogs[1].get_id());

	try
	{
		this->s_test.removeDogById(99);
	}
	catch (RepositoryException rex)
	{

	}
	
	newnrDogs = this->s_test.getNrDogs();

	assert(newnrDogs == nrDogs - 2);
}

void Test::test_update()
{
	this->s_test.addDogByVars("Bobita", "Yorkshire Terrier", 11, "https://www.pexels.com/photo/two-yellow-labrador-retriever-puppies-1108099/");
	
	std::vector<Dog> dogs = this->s_test.getAllDogs();

	assert(dogs[0].get_name() == "Bobita");
	assert(dogs[0].get_breed() == "Yorkshire Terrier");
	assert(dogs[0].get_age() == 11);
	assert(dogs[0].get_photoLink() == "https://www.pexels.com/photo/two-yellow-labrador-retriever-puppies-1108099/");

	this->s_test.updateDogById(dogs[0].get_id(), "a", "a", 2, "a");

	try
	{ 
		this->s_test.updateDogById(99, "a", "a", 2, "a");
	}
	catch (int ex)
	{

	}

	dogs = this->s_test.getAllDogs();

	assert(dogs[0].get_name() == "a");
	assert(dogs[0].get_breed() == "a");
	assert(dogs[0].get_age() == 2);
	assert(dogs[0].get_photoLink() == "a");

	dogs[0].ToString();
}

void Test::run_tests()
{
	test_add();
	test_remove();
	test_update();
}