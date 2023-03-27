#pragma once

#define END_KEY 'x'
#define ENTER_KEY '\n'
const int T = 2;

typedef struct {
	myString attribute;
	myString value;
} AttributeNode;
typedef struct {
	List<myString> selectorList;
	List<AttributeNode> attributeList;
} Section;

struct ExternalNode{
	unsigned short int counter;
	Section* sections;

	ExternalNode() : counter(0), sections(new Section[T]) {};
	~ExternalNode() 
	{
		delete[] sections;
	}
};