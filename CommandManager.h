#pragma once
class CommandManager {
	friend class Processor;
private:
	const int neverUsedChar = '@';
	int firstNumber;
	char middleChar;

	int secondNumber;
	char endChar;
	myString lastAttribute;
	myString firstAttribute;

	CommandDispatchConfig config;
private:
	void handleInput(const myString& input)
	{
		const int asciiMinNum = 48, asciiMaxNum = 57;
		myString firstNumberStr = "", secondNumberStr = "";
		int i = 0;

		reset();
		if (input.getSize() == 2) //	"?\0"
		{
			config.singleCharacterCommand = true;
			return;
		}
		//before first ,
		for (i = 0; i < input.getSize(); i++)
		{
			if (input[i] == ',') {
				i++;
				break;
			}
			else if ((int)input[i] >= asciiMinNum && (int)input[i] <= asciiMaxNum) {
				firstNumberStr.pushCharAtEnd(input[i]);
				config.firstIsNumber = true;
			}
			else
				firstAttribute.pushCharAtEnd(input[i]);
		}

		middleChar = input[i++];
		i++; //to skip second ','
		for (i; i < input.getSize(); i++)
		{
			if (input[i] == '?' || input[i] == '*')
			{
				endChar = input[i];
				config.lastIsSymbol = true;
				break;
			}
			else if ((int)input[i] >= asciiMinNum && (int)input[i] <= asciiMaxNum)//it's a number
			{
				for (i; i < input.getSize() - 1; i++)//-1, without '\0'
					secondNumberStr.pushCharAtEnd(input[i]);
				config.lastIsNumber = true;
				break;
			}
			else //it's attribute
			{
				for (i; i < input.getSize(); i++)
					lastAttribute.pushCharAtEnd(input[i]);
				config.lastIsAttribute = true;
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
		lastAttribute = firstAttribute = "";
		config = { false, false, false, false, false };
	}
};