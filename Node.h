#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node* prev;
	Node* next;
	
	Node(){}
	Node(const T& dt, Node* p = nullptr, Node* n = nullptr) : data(dt), prev(p),next(n) {};
	~Node(){}

	friend ostream& operator<<(ostream& os, const Node& node)
	{
		os << node.data << endl;
		return os;
	}
};