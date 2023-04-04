#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node* prev = nullptr;
	Node* next = nullptr;
	
	Node(){}
	Node(const Node<T>& temp)
	{
		data = temp.data;
		prev = temp.prev;
		next = temp.next;
	}
	Node(const T& dt, Node* p = nullptr, Node* n = nullptr) : data(dt), prev(p),next(n) {};
	~Node() { next = nullptr; prev = nullptr; }

	friend ostream& operator<<(ostream& os, const Node& node)
	{
		os << node.data << endl;
		return os;
	}
};