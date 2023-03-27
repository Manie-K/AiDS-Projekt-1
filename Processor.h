#pragma once
#include <iostream>
#include "myString.h"
#include "Node.h"
#include "List.h"
#include "Types.h"

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
			modeCSS = true;
			questionCounter = 0;
			currentInputString = "";
			skip = true;
		}
		if (starCounter == 4)
		{
			currentInputString = "";
			modeCSS = false;
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
			{
				cout << "? == " << numberOfSections << "\n";
				return;
			}
			if (manager.lastIsNumber && manager.middleChar =='S')//only one such command
			{

				
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

class CommandManager {
	friend class Processor;
private:
	const int neverUsedChar = '@';
	int firstNumber;
	char middleChar;

	int secondNumber;
	char endChar;
	myString lastAttribute;
	
	bool lastIsNumber;
	bool lastIsSymbol;
	bool lastIsAttribute;
	bool singleCharacterCommand;
private:
	void handleInput(const myString& input)
	{
		const int asciiMinNum = 48, asciiMaxNum = 57;
		myString firstNumberStr = "", secondNumberStr = "";
		int i = 0;
		
		reset();
		if (input.getSize() == 2) //	"?\0"
		{
			singleCharacterCommand = true;
			return;
		}
		for (i = 0; i < input.getSize(); i++)
		{
			if (input[i] == ',') {
				i++;
				break;
			}
			else
				firstNumberStr.pushCharAtEnd(input[i]);
		}
		
		middleChar = input[i++];
		
		for (i; i < input.getSize(); i++)
		{
			if (input[i] == '?' || input[i] == '*')
			{
				endChar = input[i];
				lastIsSymbol = true;
				break;
			}
			else if ((int)input[i] >= asciiMinNum && (int)input[i] <= asciiMaxNum)//it's a number
			{
				for (i; i < input.getSize()-1; i++)//-1, without '\0'
					secondNumberStr.pushCharAtEnd(input[i]);
				lastIsNumber = true;
				break;
			}
			else //it's attribute
			{
				for (i; i < input.getSize(); i++)
					lastAttribute.pushCharAtEnd(input[i]);
				lastIsAttribute = true;
				break;
			}
		}
		firstNumber = firstNumberStr.toInt();
		secondNumber = secondNumberStr.toInt();
	}
public:
	CommandManager()
	{
		reset();
	};
	void reset()
	{
		firstNumber = secondNumber = 0;
		middleChar = endChar = neverUsedChar;
		lastAttribute = "";
		lastIsNumber = lastIsSymbol = lastIsAttribute = singleCharacterCommand = false;
	}
};