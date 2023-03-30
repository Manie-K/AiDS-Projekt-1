#define _CRT_SECURE_NO_WARNINGS
#include "Processor.h"

using namespace std;

int main()
{
	Processor CSSprocessor;
	char inputChar;

	do
	{
		inputChar = getchar();
		CSSprocessor.manageInput(inputChar);
	} while (inputChar != END_KEY);

	return 1;
}