#pragma once 

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

namespace SCL
{

// SE - NOTE: this order is not compact by C struct layout rules ... however it
// is convenient for initialisation of the list defining the parameters
struct Parameter
{
public:

	std::string name;
	bool hasValue = false;

	int (*handler)(const Parameter&, const std::string&) = nullptr;
};

struct ParameterInstance
{
public:

	const Parameter& parameter;
	std::string value;
};

}

#endif
