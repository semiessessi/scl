#include "Core.h"

#include <string>
#include <vector>

namespace SCL
{

int EntryPoint(const int argumentCount, const char* const* const arguments)
{
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

		const std::string argument = arguments[i];
		if (inQuotes)
		{
			currentParameter += argument.substr(1, argument.size() - 1);
		}
		else
		{
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

	for (size_t u = 0; u < inputs.size(); ++u)
	{

	}

	return 0;
}

}
