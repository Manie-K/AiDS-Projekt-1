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
		}
		else {
			starCounter = 0;
		}
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
			if (manager.config.singleCharacterCommand)
			{	// ? == x
				cout << "? == " << numberOfSections << "\n";
				return;
			}
			if (manager.config.lastIsNumber && manager.middleChar =='S')
			{	// i S j
				Section section = getXsection(manager.firstNumber).section;
				if (section.alive && section.selectorList.getSize()>manager.secondNumber-1) 
				{
					cout << manager.firstNumber << ",S," << manager.secondNumber << " == ";
					if (manager.secondNumber == 1)
						cout << section.selectorList.getFirst()->data;
					else
						cout << section.selectorList.getAfter(manager.secondNumber - 1)->data;
					cout << "\n";
				}
				return;
			}
			if (manager.config.lastIsAttribute)
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
			if (manager.config.firstIsNumber)
			{
				if (manager.middleChar == 'S')// i S ?
				{
					int count = 0;
					Section section = getXsection(manager.firstNumber).section;
					if (section.alive) {
						count = section.selectorList.getSize();
						cout << manager.firstNumber << ",S,? == " << count << "\n";
					}
					return;
				}
				if (manager.middleChar == 'A')// i A ?
				{

					return;
				}
				if (manager.middleChar == 'D')// i D *
				{
					if (deleteSection(manager.firstNumber))
						cout << manager.firstNumber << ",D,* == deleted\n";
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
		CSS.getAfter(whichExternalNode)->data.aliveCount++;
		CSS.getAfter(whichExternalNode)->data.sections[index].selectorList = section->selectorList;
		CSS.getAfter(whichExternalNode)->data.sections[index].attributeList = section->attributeList;
		CSS.getAfter(whichExternalNode)->data.sections[index].alive = true;
	}
	void addNewNodeAndSection() 
	{
		Node<ExternalNode>* newNode = new Node<ExternalNode>;
		CSS.addLast(*newNode);
		CSS.getLast()->data.counter++;
		CSS.getLast()->data.aliveCount++;
		CSS.getLast()->data.sections[0].selectorList = section->selectorList;
		CSS.getLast()->data.sections[0].attributeList = section->attributeList;
		CSS.getLast()->data.sections[0].alive = true;
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
	SectionAndBlockNumber getXsection(int x)
	{
		int skipped = 0;
		Node<ExternalNode>* external = CSS.getFirst();
		while (external != nullptr)
		{
			if (x > external->data.aliveCount)
			{
				x -= external->data.aliveCount;
				external = external->next;
				skipped++;
				break;
			}
			else
			{
				int i = -1;
				do
				{
					i++;
					if (external->data.sections[i].alive)
					{
						x--;
					}
				} while (x > 0);
				return { external->data.sections[i],skipped};
			}

		}
		Section section;
		section.alive = false; //we have to check if section returned is alive
		return { section,  skipped};
	}
	bool deleteSection(int x)
	{
		SectionAndBlockNumber temp = getXsection(x);
		Section section = temp.section;
		if (!section.alive)
			return false;
		Node<ExternalNode>* node = nullptr;
		int index = temp.n;
		if (index > 0)
			node = CSS.getAfter(index-1);
		else
			node = CSS.getFirst();

		if (section.alive) //such section exist
		{
			section.alive = false;
			section.attributeList.deleteList();
			section.selectorList.deleteList();
			node->data.aliveCount--;
			numberOfSections--;
			if (node->data.aliveCount <= 0)
			{
				if (index > 0)
					CSS.deleteAfter(index - 1);
				else
					CSS.deleteFirst();
				CSS.decrementSize();
				
			}
		}
		return true;
	}
};

