#pragma once
#include <string>
#include "Dog.h"
// Dog validator module.

class ValidationException : public std::exception
{
private:
	std::string message;

public:
	ValidationException(std::string _message);
	const char* what() const noexcept override;
};

/////////////////////////////////////////

class DogValidator
{
public:
	static void validate(Dog d);
};