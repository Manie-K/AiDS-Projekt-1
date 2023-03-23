#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "myString.h"

using namespace std;

int main()
{
	myString str;
	str = "halo";
	myString xd;
	cout << "!\n";
	xd = str;
	cout << xd << " " << str;

	return 1;
}