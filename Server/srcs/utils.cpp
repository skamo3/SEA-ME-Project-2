#include "../includes/utils.h"

int PrintErrorText(const char *errorText, int errorNo)
{
	std::cout << COLOR_RED;
	std::cout << errorText;
	std::cout << COLOR_RESET << std::endl;
	return errorNo;
}

int PrintErrorText(const char *errorText, int errorNo, int value)
{
	std::cout << COLOR_RED;
	std::cout << errorText << " : " << value;
	std::cout << COLOR_RESET << std::endl;
	return errorNo;
}

void PrintSuccessText(const char *Text)
{
	std::cout << COLOR_RED;
	std::cout << Text;
	std::cout << COLOR_RESET << std::endl;
}