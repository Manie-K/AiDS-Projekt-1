#pragma once
#include <iostream>
#include "myString.h"
#include "Node.h"
#include "List.h"
#include "Types.h"
#include "CommandManager.h"
class Processor {
private:
	List<ExternalNode> CSS;

	friend class CommandManager;
	CommandManager manager;

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
		Node<ExternalNode>* startNode = new Node<ExternalNode>;
		CSS.addFirst(*startNode);
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
		if (modeManager(inputChar))
		{
			return; //nothing new to current input, just mode switch
		}
		if (modeCSS)
		{
			inputCSS(inputChar);
		}
		else
		{
			inputCommand(inputChar);
		}
	}

private:
	bool modeManager(const char inputChar) //change beetween CSS and Commands
	{
		bool skip = false;
		if (inputChar == '?' && modeCSS) // so it doesn't collide with "?" command
		{
			questionCounter++;
			skip = true;
		}
		else
			questionCounter = 0;
		if (inputChar == '*')
		{
			starCounter++;
			skip = true;
		}
		else
			starCounter = 0;

		if (questionCounter == 4)
		{
			modeCSS = false;
			questionCounter = 0;
			currentInputString = "";
			skip = true;
		}
		if (starCounter == 4)
		{
			currentInputString = "";
			modeCSS = true;
			starCounter = 0;
			skip = true;
		}
		return skip;
	}
	void inputCSS(const char inputChar)
	{
		if (inputChar == END_KEY)
			return;
		else if (inputChar == ',' || inputChar == '{')
		{
			saveSelector();
			if (inputChar == '{')
				numberOfSections++;
		}

		else if (inputChar == ':')
		{
			currentInputString.trim();
			attributeNode->data.attribute = currentInputString;
			currentInputString = "";
		}

		else if (inputChar == ';')
		{
			saveAttribute();
		}
		else if (inputChar == '}') //end of css section
		{
			endSection();
		}
		else
		{
			currentInputString.pushCharAtEnd(inputChar);
		}
	}
	void inputCommand(const char inputChar)
	{
		if(inputChar != ENTER_KEY)
			currentInputString.pushCharAtEnd(inputChar);
		else //command has ended
		{
			manager.handleInput(currentInputString);
			currentInputString = "";
			if (manager.singleCharacterCommand)
			{	// ? == x
				cout << "? == " << numberOfSections << "\n";
				return;
			}
			if (manager.lastIsNumber && manager.middleChar =='S')
			{	// i S j
				
				return;
			}
			if (manager.lastIsAttribute)
			{
				if (manager.middleChar == 'A') // i A n
				{

					return;
				}
				if (manager.middleChar == 'E') // z E n
				{

					return;
				}
				if (manager.middleChar == 'D') // i D n
				{

					return;
				}
			}
			if (manager.firstIsNumber)
			{
				if (manager.middleChar == 'S')// i S ?
				{

					return;
				}
				if (manager.middleChar == 'A')// i A ?
				{

					return;
				}
				if (manager.middleChar == 'D')// i D *
				{

					return;
				}
			}
			else
			{
				if (manager.middleChar == 'A')// n A ?
				{

					return;
				}
				if (manager.middleChar == 'D')// z S ?
				{

					return;
				}
			}
		}
	}
	void saveSelector()
	{
		currentInputString.trim();
		selector->data = currentInputString;

		Node<myString>* tempSelector = new Node<myString>(*selector);
		section->selectorList.addLast(*tempSelector);

		currentInputString = "";

		delete selector;
		selector = new Node<myString>;
	}
	void saveAttribute()
	{
		int i = 0;
		bool alreadyExist = false;
		
		currentInputString.trim();
		attributeNode->data.value = currentInputString;
		currentInputString = "";
		
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
	void addSection(int index, int whichExternalNode)
	{
		CSS.getAfter(whichExternalNode)->data.counter++;
		CSS.getAfter(whichExternalNode)->data.sections[index].selectorList = section->selectorList;
		CSS.getAfter(whichExternalNode)->data.sections[index].attributeList = section->attributeList;
	}
	void addNewNodeAndSection() 
	{
		Node<ExternalNode>* newNode = new Node<ExternalNode>;
		CSS.addLast(*newNode);
		CSS.getLast()->data.counter++;
		CSS.getLast()->data.sections[0].selectorList = section->selectorList;
		CSS.getLast()->data.sections[0].attributeList = section->attributeList;
	}
	void endSection()
	{
		currentInputString.trim();
		if (!(currentInputString == "")) //the previous character wasnt ';', so we have to save attribute 
			saveAttribute();

		Node<ExternalNode>* temp = CSS.getFirst();
		int whichExternalNode = 0;
		while (temp != nullptr)
		{
			if (temp->data.counter < T)
				break;
			temp = temp->next;
			whichExternalNode++;
		}
		if (temp == nullptr) //there isn't any empty space, need to add new node
			addNewNodeAndSection();
		else
			addSection(temp->data.counter, whichExternalNode);

		delete section;
		section = new Section;
	}
};

