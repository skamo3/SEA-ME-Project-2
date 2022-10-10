#include "../includes/utils.h"

int PrintErrorText(const char *errorText, int errorNo)
{
	printf("%s", COLOR_BRED);
	printf("%s", errorText);
	printf("%s\n", COLOR_RESET);
	return errorNo;
}

int PrintErrorText(const char *errorText, int errorNo, int value)
{
	printf("%s", COLOR_BRED);
	printf("%s : %d", errorText, value);
	printf("%s\n", COLOR_RESET);
	return errorNo;
}

void PrintSuccessText(const char *Text)
{
	printf("%s", COLOR_BGREEN);
	printf("%s", Text);
	printf("%s\n", COLOR_RESET);
}