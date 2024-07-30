#pragma once 

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

struct Parameter
{
public:

	std::string name;
	std::string value;

	bool hasValue;

	void (*handler)(const Parameter&);
};

#endif
