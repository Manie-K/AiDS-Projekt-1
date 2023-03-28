#pragma once

#define END_KEY '^'
#define ENTER_KEY '\n'
const int T = 2;

typedef struct {
	myString attribute;
	myString value;
} AttributeNode;
typedef struct {
	List<myString> selectorList;
	List<AttributeNode> attributeList;
	bool alive;
} Section;

struct ExternalNode{
	short int counter;
	short int aliveCount;
	Section* sections;

	ExternalNode() : counter(0), aliveCount(0), sections(new Section[T]) {};
	~ExternalNode() 
	{
		delete[] sections;
	}
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
	Section& section;
	int n;
};