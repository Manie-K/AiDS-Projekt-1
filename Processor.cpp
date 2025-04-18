#include "Processor.h"

Processor::Processor()
{
	Node<ExternalNode>* startNode = new Node<ExternalNode>;
	CSS.addFirst(*startNode);
	
	numberOfSections = questionCounter = starCounter = 0;

	currentInputString = "";
	modeCSS = true;
	attributes = false;
	section = new Section;
	selector = new Node<myString>;
	attributeNode = new Node<AttributeNode>;
};
Processor::~Processor()
{
	delete section;
	section = nullptr;
	delete selector;
	selector = nullptr;
	delete attributeNode;
	attributeNode = nullptr;
};
void Processor::manageInput(const char inputChar)
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
bool Processor::modeManager(const char inputChar) //change beetween CSS and Commands
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
		starCounter++;
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
void Processor::inputCSS(const char inputChar)
{
	if (inputChar == END_KEY)
		return;
	else if ((inputChar == ',' && !attributes) || inputChar == '{')
	{
		currentInputString.trim();
		if (currentInputString == "")//global attriubutes
		{
			attributes = true;
			return;
		}
		saveSelector();
		if (inputChar == '{') {
			attributes = true;
		}
	}

	else if (inputChar == ':' && attributes)
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
		attributes = false;
		endSection();
	}
	else
	{
		currentInputString.pushCharAtEnd(inputChar);
	}
}
void Processor::inputCommand(const char inputChar)
{
	if (inputChar != ENTER_KEY && inputChar != END_KEY)
		currentInputString.pushCharAtEnd(inputChar);
	else //command has ended
	{
		manager.handleInput(currentInputString);
		currentInputString = "";
		commandDispatcher();
	}
}
void Processor::saveSelector()
{
	currentInputString.trim();
	selector->data = currentInputString;

	Node<myString>* tempSelector = new Node<myString>(*selector);
	section->selectorList.addLast(*tempSelector);

	currentInputString = "";

	delete selector;
	selector = new Node<myString>;
}
void Processor::saveAttribute()
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
		section->attributeList.getAt(i)->data.value = attributeNode->data.value;
	}
	else {
		Node<AttributeNode>* tempAttr = new Node<AttributeNode>(*attributeNode);
		section->attributeList.addLast(*tempAttr);
	}

	delete attributeNode;
	attributeNode = new Node<AttributeNode>;
}
void Processor::addSection(int index, int whichExternalNode, Section& sect)
{
	CSS.getAt(whichExternalNode)->data.counter++;
	CSS.getAt(whichExternalNode)->data.aliveCount++;
	CSS.getAt(whichExternalNode)->data.sections[index].selectorList = sect.selectorList;
	CSS.getAt(whichExternalNode)->data.sections[index].attributeList = sect.attributeList;
	CSS.getAt(whichExternalNode)->data.sections[index].alive = true;
}
void Processor::addNewNodeAndSection(Section& sect)
{
	Node<ExternalNode>* newNode = new Node<ExternalNode>;
	CSS.addLast(*newNode);
	CSS.getLast()->data.counter++;
	CSS.getLast()->data.aliveCount++;
	CSS.getLast()->data.sections[0].selectorList = sect.selectorList;
	CSS.getLast()->data.sections[0].attributeList = sect.attributeList;		
	CSS.getLast()->data.sections[0].alive = true;
}
void Processor::endSection()
{
	numberOfSections++;
	currentInputString.trim();
	if (!(currentInputString == "")) //the previous character wasnt ';', so we have to save attribute 
		saveAttribute();

	Section* tempSect = new Section(*section);
	Node<ExternalNode>* temp = CSS.getFirst();
	int whichExternalNode = 0;
	while (temp != nullptr)
	{
		if (temp->data.counter < Tcount)
			break;
		temp = temp->next;
		whichExternalNode++;
	}
	if (temp == nullptr) //there isn't any empty space, need to add new node
		addNewNodeAndSection(*tempSect);
	else
		addSection(temp->data.counter, whichExternalNode, *tempSect);

	delete section;
	section = new Section;
}
bool Processor::deleteSection(int x)
{
	SectionAndBlockNumber temp = getXsection(x);
	Section* section = temp.section;
	Node<ExternalNode>* node = nullptr;
	int index = temp.n;
	node = CSS.getAt(index);
	if (section == nullptr || node == nullptr)
		return false;

	section->alive = false;
	section->attributeList.nullifyList();
	section->selectorList.nullifyList();
	node->data.aliveCount--;
	numberOfSections--;
	if (node->data.aliveCount <= 0)
	{
		if (index == 0 && CSS.getSize() <= 1)
		{
			Node<ExternalNode>* tempSect = CSS.getFirst();
			tempSect->next = nullptr;
			tempSect->prev = nullptr;
			tempSect->data.aliveCount = 0;
			tempSect->data.counter = 0;
			tempSect->data.sections = new Section[Tcount];
		}
		else
			CSS.deleteAt(index);
	}
	return true;
}
SectionAndBlockNumber Processor::getXsection(int x)
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
		}
		else
		{
			int i = -1;
			do
			{
				i++;
				if (external->data.sections[i].alive) {
					x--;
				}
			} while (x > 0);
			return { &external->data.sections[i],skipped };
		}
	}
	return { nullptr,  skipped };
}
void Processor::commandDispatcher()
{
	if (manager.config.singleCharacterCommand)
	{	// ? == x
		cout << "? == " << numberOfSections << "\n";
		return;
	}
	if (manager.config.lastIsNumber && manager.middleChar == 'S')
	{	// i S j
		if (manager.firstNumber > 0 && manager.secondNumber > 0)
			iSj_Command();
		return;
	}
	if (manager.config.lastIsAttribute)
	{
		if (manager.middleChar == 'A') // i A n
		{
			if (manager.firstNumber > 0)
				iAn_Command();
			return;
		}
		if (manager.middleChar == 'E') // z E n
		{
			zEn_Command();
			return;
		}
		if (manager.middleChar == 'D') // i D n
		{
			if (manager.firstNumber > 0)
				iDn_Command();
			return;
		}
	}
	if (manager.config.firstIsNumber)
	{
		if (manager.middleChar == 'S')// i S ?
		{
			if (manager.firstNumber > 0)
				iSquestion_Command();
			return;
		}
		if (manager.middleChar == 'A')// i A ?
		{
			if (manager.firstNumber > 0)
				iAquestion_Command();
			return;
		}
		if (manager.middleChar == 'D')// i D *
		{
			if (manager.firstNumber > 0 && deleteSection(manager.firstNumber))
				cout << manager.firstNumber << ",D,* == deleted\n";
			return;
		}
	}
	else
	{
		if (manager.middleChar == 'A')// n A ?
		{
			nAquestion_Command();
			return;
		}
		if (manager.middleChar == 'S')// z S ?
		{
			zSquestion_Command();
			return;
		}
	}
}
void Processor::iSj_Command()
{
	Section* section = getXsection(manager.firstNumber).section;
	if (section == nullptr)
		return;
	if (section->selectorList.getSize() > manager.secondNumber - 1)
	{
		if (section->selectorList.getAt(manager.secondNumber - 1) != nullptr)
		{
			myString str = section->selectorList.getAt(manager.secondNumber - 1)->data;
			if (str == "")
				return;
			cout << manager.firstNumber << ",S," << manager.secondNumber << " == ";
			cout << str << "\n";
		}
	}
}
void Processor::iAn_Command()
{
	Section* section = getXsection(manager.firstNumber).section;
	if (section != nullptr)
	{
		Node<AttributeNode>* temp = section->attributeList.getFirst();
		while (temp != nullptr)
		{
			if (temp->data.attribute == manager.lastAttribute)
			{
				cout << manager.firstNumber << ",A," << manager.lastAttribute << " == ";
				cout << temp->data.value << "\n";
				return;
			}
			temp = temp->next;
		}
	}
}
void Processor::zEn_Command()
{
	myString selector = manager.firstAttribute;
	myString attribute = manager.lastAttribute;

	Node<myString>* tempSelect = nullptr;
	Node<AttributeNode>* tempAttr = nullptr;

	Node<ExternalNode>* external = CSS.getLast();
	Section section = external->data.sections[0];

	while (external != nullptr)
	{
		int i = external->data.counter - 1;
		do
		{
			section = external->data.sections[i];
			tempSelect = section.selectorList.getFirst();
			while (tempSelect != nullptr)
			{
				if (tempSelect->data == selector) //we found selector
				{
					tempAttr = section.attributeList.getFirst();
					while (tempAttr != nullptr)
					{
						if (tempAttr->data.attribute == attribute) //we found attrbute
						{
							cout << selector << ",E," << attribute << " == ";
							cout << tempAttr->data.value << "\n";
							return;
						}
						tempAttr = tempAttr->next;
					}
					break; //no attribute duplicates
				}
				tempSelect = tempSelect->next;
			}
			i--;
		} while (i >= 0);
		external = external->prev;
	}
}
void Processor::iDn_Command()
{
	Section* section = getXsection(manager.firstNumber).section;
	if (section == nullptr)
		return;
	Node<AttributeNode>* tempAttr = section->attributeList.getFirst();
	int index = 0;
	while (tempAttr != nullptr)
	{
		if (tempAttr->data.attribute == manager.lastAttribute)
		{
			section->attributeList.deleteAt(index);
			if (section->attributeList.getSize() <= 0)
				deleteSection(manager.firstNumber);
			cout << manager.firstNumber << ",D," << manager.lastAttribute << " == deleted\n";
			return;
		}
		index++;
		tempAttr = tempAttr->next;
	}
}
void Processor::iSquestion_Command()
{
	Section* section = getXsection(manager.firstNumber).section;
	if (section != nullptr) {
		size_t count = 0;
		count = section->selectorList.getSize();
		cout << manager.firstNumber << ",S,? == " << count << "\n";
	}
}
void Processor::iAquestion_Command()
{
	Section* section = getXsection(manager.firstNumber).section;
	if (section != nullptr) {
		size_t count = section->attributeList.getSize();
		if (count > 0)
			cout << manager.firstNumber << ",A,? == " << count << "\n";
	}
}
void Processor::nAquestion_Command()
{
	int count = 0;
	Node<ExternalNode>* external = CSS.getFirst();
	Section section;
	while (external != nullptr)
	{
		int i = 0;
		do
		{
			section = external->data.sections[i];
			if (section.alive)
			{
				Node<AttributeNode>* temp = section.attributeList.getFirst();
				while (temp != nullptr)
				{
					if (temp->data.attribute == manager.firstAttribute)
					{
						count++;
						break;
					}
					temp = temp->next;
				}
			}
			i++;
		} while (i < external->data.counter);
		external = external->next;
	}
	cout << manager.firstAttribute << ",A,? == " << count << "\n";
}
void Processor::zSquestion_Command()
{
	int count = 0;
	Node<ExternalNode>* external = CSS.getFirst();
	Section section;
	while (external != nullptr)
	{
		int i = 0;
		do {
			section = external->data.sections[i];
			if (section.alive) {
				Node<myString>* temp = section.selectorList.getFirst();
				while (temp != nullptr) {
					if (temp->data == manager.firstAttribute) {
						count++;
						break;
					}
					temp = temp->next;
				}
			}
			i++;
		} while (i < external->data.counter);
		external = external->next;
	}
	cout << manager.firstAttribute << ",S,? == " << count << "\n";
}