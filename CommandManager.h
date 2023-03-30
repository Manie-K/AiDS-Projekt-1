#pragma once
#include "Types.h"

class CommandManager {
	friend class Processor;
private:
	const int neverUsedChar = '@', asciiMinNum = 48, asciiMaxNum = 57;
	int firstNumber, secondNumber;
	char middleChar, endChar;
	myString lastAttribute, firstAttribute;
	CommandDispatchConfig config;
private:
	void handleInput(const myString& in);
public:
	CommandManager();
	~CommandManager();
	void reset();
};