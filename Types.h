#pragma once
#include <iostream>
#include "myString.h"
#include "Node.h"
#include "newList.h"

#define END_KEY '\xff'
#define ENTER_KEY '\n'
#define Tcount 8

struct AttributeNode {
	myString attribute;
	myString value;
};

struct Section{
	List<myString> selectorList;
	List<AttributeNode> attributeList;
	bool alive = true;
	~Section() {
		selectorList.nullifyList();
		attributeList.nullifyList();
	}
};

struct ExternalNode{
	short int counter;
	short int aliveCount;
	Section* sections;

	ExternalNode() : counter(0), aliveCount(0), sections(new Section[Tcount]) {};
	~ExternalNode() {delete[] sections;}
};

struct CommandDispatchConfig {
	bool lastIsNumber;
	bool lastIsSymbol;
	bool lastIsAttribute;
	bool singleCharacterCommand;
	bool firstIsNumber;
};

struct SectionAndBlockNumber
{
	Section* section;
	int n;
};