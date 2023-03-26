#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "myString.h"
#include "Node.h"
#include "List.h"
#include "Types.h"

using namespace std;

int main()
{
	List<ExternalNode> CSS;
	Node<ExternalNode> startNode;
	CSS.addFirst(startNode);
	CSS.incrementSize();

	int numberOfSections = 0;
	char inputChar;
	myString currentInputString = "";
	
	Section* section = new Section;
	Node<myString>* selector = new Node<myString>;
	Node<AttributeNode>* attributeNode = new Node<AttributeNode>;
	

	while (cin >> inputChar)
	{
		if (inputChar == 'x')
			break;
		if (inputChar == ' ')
			continue;
		else if (inputChar == ',')
		{
			selector->data = currentInputString;
			section->selectorList.addLast(*selector);
			currentInputString = "";

			delete selector;
			selector = new Node<myString>;
		}
		else if (inputChar == '{') //start of css section
		{
			selector->data = currentInputString;
			section->selectorList.addLast(*selector);
			currentInputString = "";

			delete selector;
			selector = new Node<myString>;
			numberOfSections++;
		}

		else if (inputChar == ':')
		{
			attributeNode->data.attribute = currentInputString;
			currentInputString = "";
		}

		else if (inputChar == ';' || (inputChar=='}' && !(currentInputString == "")))
		{

			attributeNode->data.value = currentInputString;
			currentInputString = "";
			section->attributeList.addLast(*attributeNode);
			delete attributeNode;
			attributeNode = new Node<AttributeNode>;
		}
		else if (inputChar == '}') //end of css section
		{
			Node<ExternalNode>* temp = CSS.getFirst();
			int whichExternalNode = 0;
			while (temp!=nullptr)
			{
				if (temp->data.counter < T)
					break;
				temp = temp->next;
				whichExternalNode++;
			}
			if (temp == nullptr)
			{
				Node<ExternalNode> newNode;
				CSS.addLast(newNode);
				CSS.incrementSize();
				CSS.getLast()->data.sections[0] = *section;
				CSS.getLast()->data.counter++;
			}
			else
			{
				int index = temp->data.counter;
				CSS.getAfter(whichExternalNode)->data.counter++;
				CSS.getAfter(whichExternalNode)->data.sections[index] = *section;
			}

			delete temp;
			delete section;
			section = new Section;
		}
		else
		{
			currentInputString.pushCharAtEnd(inputChar);
		}
	}
	CSS.display();

	return 1;
}