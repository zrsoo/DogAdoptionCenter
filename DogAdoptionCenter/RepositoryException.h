#pragma once
#include <string>
// Repository Exception module.

class RepositoryException : public std::exception
{
private:
	std::string message;

public:
	RepositoryException(std::string _message);
	const char* what() const noexcept override;
	std::string getMessage();
};

inline RepositoryException::RepositoryException(std::string _message) : message{_message}
{
}

inline const char *RepositoryException::what() const noexcept
{
	return message.c_str();
}

inline std::string RepositoryException::getMessage()
{
	return this->message;
}