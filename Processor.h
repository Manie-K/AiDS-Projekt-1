#pragma once
#include <iostream>
#include "myString.h"
#include "Node.h"
#include "List.h"
#include "Types.h"

class Processor {
private:
	List<ExternalNode> CSS;

	bool modeCSS;
	int starCounter;
	int questionCounter;
	int numberOfSections;
	myString currentInputString;

	Section* section;
	Node<myString>* selector;
	Node<AttributeNode>* attributeNode;

public:
	Processor()
	{
		Node<ExternalNode> startNode;
		CSS.addFirst(startNode);
		numberOfSections = 0;
		questionCounter = 0;
		starCounter = 0;
		currentInputString = "";
		modeCSS = true;
		section = new Section;
		selector = new Node<myString>;
		attributeNode = new Node<AttributeNode>;
	};
	~Processor()
	{
		delete section;
		section = nullptr;
		delete selector;
		selector = nullptr;
		delete attributeNode;
		attributeNode = nullptr;
	};

	void manageInput(const char inputChar)
	{
		modeCSS = modeManager(inputChar);

		if (modeCSS)
		{
			inputCSS(inputChar);
		}
		else
		{
			inputCommand(inputChar);
		}
	}



	bool modeManager(const char inputChar) //change beetween CSS and Commands
	{
		bool css = modeCSS;
		if (inputChar == '?')
			questionCounter++;
		else
			questionCounter = 0;
		if (inputChar == '*')
			starCounter++;
		else
			starCounter = 0;

		if (questionCounter == 4)
		{
			css = true;
			questionCounter = 0;
		}
		if (starCounter == 4)
		{
			css = false;
			starCounter = 0;
		}
		return css;
	}

	void inputCSS(const char inputChar)
	{
		if (inputChar == 'x')
			return;
		else if (inputChar == ',' || inputChar == '{')
		{
			currentInputString.trim();
			selector->data = currentInputString;
			Node<myString>* tempSelector = new Node<myString>(*selector);
			section->selectorList.addLast(*tempSelector);
			currentInputString = "";

			delete selector;
			selector = new Node<myString>;
			if (inputChar == '{')
				numberOfSections++;
		}

		else if (inputChar == ':')
		{
			currentInputString.trim();
			attributeNode->data.attribute = currentInputString;
			currentInputString = "";
		}

		else if (inputChar == ';' || (inputChar == '}' && !(currentInputString == "")))
		{
			currentInputString.trim();
			attributeNode->data.value = currentInputString;
			currentInputString = "";
			bool alreadyExist = false;
			int i = 0;
			Node<AttributeNode>* temp = section->attributeList.getFirst();
			while (temp != nullptr)
			{
				if (temp->data.attribute == attributeNode->data.attribute)
				{
					alreadyExist = true;
					break;
				}
				temp = temp->next;
				i++;
			}
			if (alreadyExist) {
				section->attributeList.getAfter(i)->data.value = attributeNode->data.value;
			}
			else {
				Node<AttributeNode>* tempAttr = new Node<AttributeNode>(*attributeNode);
				section->attributeList.addLast(*tempAttr);
			}
			delete attributeNode;
			attributeNode = new Node<AttributeNode>;
		}
		else if (inputChar == '}') //end of css section
		{
			Node<ExternalNode>* temp = CSS.getFirst();
			int whichExternalNode = 0;
			while (temp != nullptr)
			{
				if (temp->data.counter < T)
					break;
				temp = temp->next;
				whichExternalNode++;
			}
			if (temp == nullptr)
			{
				Node<ExternalNode>* newNode = new Node<ExternalNode>;
				CSS.addLast(*newNode);
				CSS.getLast()->data.counter++;
				CSS.getLast()->data.sections[0].selectorList = section->selectorList;
				CSS.getLast()->data.sections[0].attributeList = section->attributeList;
			}
			else
			{
				int index = temp->data.counter;
				CSS.getAfter(whichExternalNode)->data.counter++;
				CSS.getAfter(whichExternalNode)->data.sections[index].selectorList = section->selectorList;
				CSS.getAfter(whichExternalNode)->data.sections[index].attributeList = section->attributeList;
			}

			delete section;
			section = new Section;
		}
		else
		{
			currentInputString.pushCharAtEnd(inputChar);
		}
	}

	void inputCommand(const char inputChar) {}
};