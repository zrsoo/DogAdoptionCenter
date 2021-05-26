// Storage module...
#include <string>
#include "Service.h"
#include "Dog.h"
#pragma once

// Base abstract class for CSVStorage and HTMLStorage classes.
class Storage
{
protected:
	std::string _filename;
public:
	Storage(std::string filename);
	virtual ~Storage();

	std::string get_filename() const;
	virtual void write_to_file(Service s) const = 0;
	virtual void open_file() const = 0;
};

// CSVStorage class.
class CSVStorage : public Storage
{
public:
	CSVStorage(std::string filename);
	~CSVStorage();

	void write_to_file(Service s) const override;
	void open_file() const override;
};

// HTMLStorage class.
class HTMLStorage : public Storage
{
public:
	HTMLStorage(std::string filename);
	~HTMLStorage();

	void write_to_file(Service s) const override;
	void open_file() const override;
};