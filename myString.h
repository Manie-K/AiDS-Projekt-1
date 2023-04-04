#include <iostream>
#include <string.h>

#define END_KEY '\xff'
#define ENTER_KEY '\n'
#define SPACE_KEY ' '
#define STR_END_KEY '\0'
#define TAB_KEY '\t'
#define CARRIAGE_KEY '\r'
#define VERT_TAB_KEY '\v'
#define FORM_KEY '\f'

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
	void pushCharAtEnd(const char ch);
	void trim();
	int toInt() const;

	//getters/setters
	size_t getSize() const;

	//operators
	friend ostream& operator<<(ostream& os, const myString& s);
	
	bool operator==(const myString& s) const;

	myString& operator=(const myString& s);
	myString& operator=(const char* s);
	
	char operator[](size_t index) const;
};