#include <iostream>
#include <string.h>

using namespace std;

class myString {
private:
	size_t size;
	char* data;
public:
	myString() { size = 0; data = nullptr; }
	~myString() { delete[] data; }
	
	myString(const char* newData) 
	{
		size = strlen(newData)+1;
		data = new char[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = newData[i];
		}
	}

	myString(const myString& temp)
	{
		size = temp.size;
		data = new char[size];
		for (int i = 0; i < size; i++) {
			data[i] = temp.data[i];
		}
	}

	friend ostream& operator<<(ostream& os, const myString& s)
	{
		os << s.data;
		return os;
	}
	
	bool operator==(const myString& s) 
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

	myString& operator=(const myString& s)
	{
		if (data != nullptr)
			delete[] data;
		size = s.size;
		data = new char[size];
		for (int i = 0; i < size; i++)
			data[i] = s.data[i];
		return *this;
	}

	myString& operator=(const char* s)
	{
		if (data != nullptr)
			delete[] data;
		size = strlen(s)+1;
		data = new char[size];
		for (int i = 0; i < size; i++)
			data[i] = s[i];
		return *this;
	}

};