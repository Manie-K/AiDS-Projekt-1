#include "CommandManager.h"

CommandManager::CommandManager(){reset();};

CommandManager::~CommandManager() {}

void CommandManager::reset()
{
	firstNumber = secondNumber = 0;
	middleChar = ' ';
	lastAttribute = firstAttribute = "";
	config = { false, false, false, false, false };
}

void CommandManager::handleInput(const myString& in)
{
	myString input = in, firstNumberStr = "", secondNumberStr = "";
	int i = 0;
	bool isNumber = false;

	input.trim();
	reset();

	if (input == "?") {
		config.singleCharacterCommand = true;
		return;
	}
	//before first ","
	for (i = 0; i < input.getSize(); i++) {
		if (i == 0 && ((input[i] >= asciiMinNum && (int)input[i] <= asciiMaxNum) || input[i] == '-'))
			isNumber = true;
		if (input[i] == ',') {
			i++;
			break;
		}
		else if (isNumber && (int)input[i] >= asciiMinNum && (int)input[i] <= asciiMaxNum) {
			firstNumberStr.pushCharAtEnd(input[i]);
			config.firstIsNumber = true;
		}
		else
			firstAttribute.pushCharAtEnd(input[i]);
	}

	middleChar = input[i++];
	i++; //to skip second ','

	for (i; i < input.getSize(); i++) {
		if (input[i] == '?' || input[i] == '*') {
			config.lastIsSymbol = true;
			break;
		}
		else if ((int)input[i] >= asciiMinNum && (int)input[i] <= asciiMaxNum) {
			for (i; i < input.getSize() - 1; i++)//-1, without '\0'
				secondNumberStr.pushCharAtEnd(input[i]);
			config.lastIsNumber = true;
			break;
		}
		else {
			for (i; i < input.getSize(); i++)
				lastAttribute.pushCharAtEnd(input[i]);
			config.lastIsAttribute = true;
			break;
		}
	}

	if (!(firstNumberStr == ""))
		firstNumber = firstNumberStr.toInt();
	if (!(secondNumberStr == ""))
		secondNumber = secondNumberStr.toInt();
}
