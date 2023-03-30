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

	//List<myString> list;

	//Node<myString> a1, a2, a3, a4;
	//a1.data = "1";
	//a2.data = "2 ";
	//a3.data = "3";
	//a4.data = "4\t";


	//list.addLast(a2);
	//list.addLast(a3);
	//list.addFirst(a4);
	//list.addFirst(a1);

	//int i = 1;
	//Node<myString>* temp = list.getFirst();
	//while (temp != nullptr) {
	//	cout << i++ << ". " << temp->data << "\n";
	//	temp = temp->next;
	//}
	return 1;
}