#include "Core.h"
#include "Parameter.h"

// SE - TODO: a better way to link with the project config. ffs.

#include "../../Code/Core/Project_Config.h"

#include <string>
#include <vector>

namespace SCL
{

// SE - TODO: this should probably live in a Parameter.cpp once it exists
const Parameter Parameter::Free = { "free" };

int EntryPoint(const int argumentCount, const char* const* const arguments
	/*, const SCL::Parameter* const parameters*/)
{
	// sort out quotes and get a "true" list of the input parameters
	std::string currentParameter = "";
	std::vector<std::string> inputs;
	char inQuotes = '\0';
	for (int i = 1; i < argumentCount; ++i)
	{
		// SE - TODO: this should never happen really?
		if (strlen(arguments[i]) == 0)
		{
			continue;
		}

		if ((arguments[i][0] == '"')
			|| (arguments[i][0] == '\''))
		{
			inQuotes = arguments[i][0];
		}

		std::string argument = arguments[i];
		if (inQuotes)
		{
			currentParameter += argument.substr(1, argument.size() - 1);
		}
		else
		{
			// remove switch prefixes.
			while ((argument[0] == '-')
				|| (argument[0] == '/'))
			{
				argument = argument.substr(1, argument.size() - 1);
			}

			currentParameter = argument;
			inputs.push_back(currentParameter);
		}

		if ((inQuotes != '\0')
			&& (currentParameter.back() == inQuotes))
		{
			inQuotes = '\0';
			currentParameter.pop_back();
			inputs.push_back(currentParameter);
		}
	}

	std::vector<ParameterInstance> parameters;
	const SCL::Parameter* currentOption = &SCL::Parameter::Free;
	const size_t possibleParameterCount =
		sizeof(kSCLParameters) / sizeof(SCL::Parameter);
	bool nextParameterIsValue = false;
	for (size_t u = 0; u < inputs.size(); ++u)
	{
		if (nextParameterIsValue == true)
		{
			// its a known parameter
			const ParameterInstance parameter =
			{
				*currentOption,
				inputs[u]
			};
			parameters.push_back(parameter);
			nextParameterIsValue = false;
			currentOption = &SCL::Parameter::Free;
			continue;
		}

		currentOption = &SCL::Parameter::Free;
		nextParameterIsValue = false;
		for (size_t v = 0; v < possibleParameterCount; ++v)
		{
			if (kSCLParameters[v].name == inputs[u])
			{
				if (kSCLParameters[v].hasValue)
				{
					// its a switch/label for the next parameter
					nextParameterIsValue = true;
				}
				currentOption = &kSCLParameters[v];
				break;
			}
		}

		if (nextParameterIsValue == false)
		{
			// its a "free" parameter, or a standalone flag.
			// the logic is the same
			const ParameterInstance parameter =
			{
				*currentOption,
				inputs[u]
			};
			parameters.push_back(parameter);
			continue;
		}
	}

	return 0;
}

}
