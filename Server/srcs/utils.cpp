#include "../includes/utils.h"

int PrintErrorText(const std::string &errorText, int errorNo)
{
	std::cout << COLOR_RED;
	std::cout << errorText;
	std::cout << COLOR_RESET << std::endl;
	return errorNo;
}

int PrintErrorText(const std::string &errorText, int errorNo, int value)
{
	std::cout << COLOR_RED;
	std::cout << errorText << " : " << value;
	std::cout << COLOR_RESET << std::endl;
	return errorNo;
}

void PrintSuccessText(const std::string &Text)
{
	std::cout << COLOR_RED;
	std::cout << Text;
	std::cout << COLOR_RESET << std::endl;
}