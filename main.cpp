#define _CRT_SECURE_NO_WARNINGS
#include "Processor.h"

using namespace std;

int main()
{
	Processor processor;
	char inputChar;

	do
	{
		inputChar = getchar();
		processor.manageInput(inputChar);
	} while (inputChar != END_KEY);
	
	return 1;
}