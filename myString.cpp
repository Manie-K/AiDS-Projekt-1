#include "myString.h"

myString::myString() { size = 0; data = nullptr; }
myString::~myString() { delete[] data; }

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
	}
}

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
	return '?';
}