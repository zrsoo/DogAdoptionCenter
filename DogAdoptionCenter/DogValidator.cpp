#include "DogValidator.h"
#include <algorithm>
// Dog validator implementation

ValidationException::ValidationException(std::string _message) : message{ _message }
{
}

const char* ValidationException::what() const noexcept
{
	return message.c_str();
}

/////////////////////////////////////////

void DogValidator::validate(Dog d)
{
	std::string breed = d.get_breed();
	std::string name = d.get_name();
	int age = d.get_age();
	std::string photo_link = d.get_photoLink();

	// Checking if breed contains any numbers...
	if (std::any_of(breed.begin(), breed.end(), ::isdigit))
		throw ValidationException("Breed cannot contain any numbers!");

	// Checking if name is written nicely...
	
	if (std::any_of(name.begin() + 1, name.end(), ::isupper))
		throw ValidationException("Only the first letter in the name can be uppercase!");

	// Checking for all the fields to be non-empty...
	if (breed == "" || name == "" || photo_link == "")
		throw ValidationException("All fields must contain something!");

	// Checking for age to be appropriate...
	if (age <= 0)
		throw ValidationException("Invalid age!");
}