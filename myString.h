#include <iostream>
#include <string.h>

using namespace std;

class myString {
private:
	size_t size;
	char* data;
public:
	//constructors
	myString();
	myString(const char* newData);
	myString(const myString& temp);

	~myString();

	//methods
	void pushCharAtEnd(char ch);

	//operators
	friend ostream& operator<<(ostream& os, const myString& s);
	
	bool operator==(const myString& s) const;

	myString& operator=(const myString& s);
	myString& operator=(const char* s);
	
	char operator[](size_t index) const;
};