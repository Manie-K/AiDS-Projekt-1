#define _CRT_SECURE_NO_WARNINGS
#include "Processor.h"

using namespace std;

int main()
{
	//Processor processor;
	//char inputChar;

	//do
	//{
	//	inputChar = getchar();
	//	processor.manageInput(inputChar);
	//} while (inputChar != END_KEY);

	List<myString> list;

	Node<myString> a1, a2, a3, a4;
	a1.data = "1 ";
	a2.data = "2 ";
	a3.data = "3 ";
	a4.data = "4 ";

	list.addFirst(a2);
	list.addFirst(a1);
	list.addLast(a3);
	list.addLast(a4);

	list.deleteAt(1);
	list.deleteAt(1);


	return 1;
}