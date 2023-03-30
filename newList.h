#pragma once
#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
class List
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;
public:
	List() :size(0), first(nullptr), last(nullptr) {}
	~List() {}
	void deleteList(){}

	size_t getSize() { return size; }
	void addFirst(Node<T>& node)
	{
		if (size == 0)
		{
			first = new Node<T>(node);
			first->next = nullptr;
			first->prev = nullptr;
			last = first;
			size = 1;
			return;
		}
		node.next = first;
		node.prev = nullptr;
		first->prev = &node;
		first = &node;
		size++;
	}
	void addLast(Node<T>& node)
	{
		if (size == 0)
		{
			addFirst(node);
			return;
		}
		node.next = nullptr;
		node.prev = last;
		last->next = &node;
		last = &node;
		size++;
	}
	Node<T>* getFirst(){return first; }
	Node<T>* getLast(){ return last; }
	Node<T>* getAt(int index)
	{
		if (index == 0)
			return getFirst();
		if (index == size - 1)
			return getLast();
		if (index < 0 || index > size - 1)
			return nullptr;
		Node<T>* temp = first;
		int i = 0;
		while (temp != nullptr && i < index)
		{
			i++;
			temp = temp->next;
		}
		return temp;
	}
	
	void deleteFirst()
	{
		if (size <= 0)
			return;
		if (size == 1)
		{
			delete first;
			first = nullptr;
			last = nullptr;
			size--;
		}
		if (first != nullptr) {
			first = first->next;
			delete first->prev;
			first->prev = nullptr;
			size--;
			return;
		}
	}
	void deleteLast()
	{
		if (size <= 0)
			return;
		if (size == 1)
		{
			deleteFirst();
			return;
		}
		if (last != nullptr)
		{
			last = last->prev;
			delete last->next;
			last->next = nullptr;
			size--;
			return;
		}
	}
	void deleteAt(int index)
	{
		if (index == 0)
		{
			deleteFirst();
			return;
		}
		if (index == size - 1)
		{
			deleteLast();
			return;
		}
		if (index < 0 || index > size - 1)
			return;
		
		Node<T>* temp = first;
		int i = 0;
		while (i < index)
		{
			if (temp == nullptr)
				return;
			i++;
			temp = temp->next;
		}
		if (temp == nullptr)
			return;
		if (temp->next != nullptr)
		{
			temp->next->prev = temp->prev;
		}
		if (temp->prev != nullptr)
		{
			temp->prev->next= temp->next;
		}
		size--;
		delete temp;
		temp = nullptr;
	}
};