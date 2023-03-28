#include "myString.h"

myString::myString() { size = 0; data = nullptr; }
myString::~myString() { 
	delete[] data; 
}

myString::myString(const char* newData)
{
	size = strlen(newData) + 1;
	data = new char[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = newData[i];
	}
}

myString::myString(const myString& temp)
{
	size = temp.size;
	data = new char[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = temp.data[i];
	}
}

void myString::pushCharAtEnd(const char ch)
{
	if (ch != '\0')
	{
		char* temp = new char[size];
		for (int i = 0; i < size; i++)
			temp[i] = data[i];
		delete[] data;
		size++;
		data = new char[size];

		for (int i = 0; i < size - 2; i++)
		{
			data[i] = temp[i];
		}
		data[size - 2] = ch;
		data[size - 1] = '\0';

		delete[] temp;
		temp = nullptr;
	}
}

void myString::trim()
{
	if (size == 1)
		return;
	int beginCount = 0;
	int endCount = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (data[i] == '\0' || data[i] == ' ' || data[i] == '\n' || data[i] == '\t' || data[i] == '\r' || data[i] == '\v' || data[i] == '\f')
			beginCount++;
		else
			break;
	}

	for (int i = size - 1; i >= 0; i--)
	{
		if (data[i] == '\0' || data[i] == ' ' || data[i] == '\n' || data[i] == '\t' || data[i] == '\r' || data[i] == '\v' || data[i] == '\f')
			endCount++;
		else
			break;
	}

	if (beginCount + endCount >= size)
	{
		delete[] data;
		data = new char[1];
		data[0] = '\0';
		size = 1;
		return;
	}
	int newSize = size + 1 - endCount - beginCount;

	char* tab = new char[newSize];
	for (int i = beginCount; i <= size-endCount; i++)
	{
		tab[i - beginCount] = data[i];
	}
	tab[newSize - 1] = '\0';
	delete[] data;
	size = newSize;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = tab[i];
	data[size - 1] = '\0';
	delete[] tab;  
}

int myString::toInt() const
{
	if (data == "") 
		return 0;
	const int asciiOffset = 48;
	int result = 0;
	int tenPower = 1;

	for (int i = size - 2; i >= 0; i--)
	{
		if (data[i] == '-')
		{
			result *= -1;
			continue;
		}
		result += (int)(data[i] - asciiOffset) * tenPower;
		tenPower *= 10;
	}

	return result;
}

size_t myString::getSize() const{ return size; }

ostream& operator<<(ostream& os, const myString& s)
{
	os << s.data;
	return os;
}

bool myString::operator==(const myString& s) const
{
	if (s.size != this->size)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (data[i] != s.data[i])
			return false;
	}
	return true;
}

myString& myString::operator=(const myString& s)
{
	delete[] data;
	size = s.size;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = s.data[i];
	return *this;
}

myString& myString::operator=(const char* s)
{
	delete[] data;
	size = strlen(s) + 1;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = s[i];
	return *this;
}

char myString::operator[](size_t index) const
{
	if (index >= 0 && index < size)
		return (char)data[index];
	return ' ';
}