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
	~List()
	{
		
	}

	void deleteList()
	{
		//TODO
	}

	void addFirst(Node<T>& node)
	{
		size++;
		node.next = first;
		node.prev = nullptr;
		if (first != nullptr)
			first->prev = &node;
		first = &node;
		if (size == 1) //just added first element so-> last nullptr => first
		{
			last = first;
		}
	}

	void deleteFirst()
	{
		if (this == nullptr)
			return;
		size--;
		if (size == 0) {
			delete first;
			first = nullptr;
		}
		else {
			if (first == nullptr) {
				delete first;
				first = nullptr;
			}
			else {
				first = first->next;
				delete first->prev;
				first->prev = nullptr;
			}
		}
	}

	void addLast(Node<T>& node)
	{
		size++;
		node.next = nullptr;
		node.prev = last;
		if (last != nullptr)
			last->next = &node;
		last = &node;
		if (size == 1)
		{
			first = last;
		}

	}

	void deleteLast()
	{
		if (size==0) {
			return;
		}
		size--;
		Node<T>* temp = last;
		if (first== last) {
			first= last = nullptr;
		}
		else {
			last = last->prev;
			last->next = nullptr;
		}
		delete temp;
	}

	void addAfter(Node<T>& node, size_t index) //index from 0, so:  addAfter(0) adds after first, addAfter(1) adds after second
	{
		if (index >= size - 1)
			return;
		size++;
		Node<T>* current = first;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		//adding after current
		node.next = current->next->next;
		node.prev = current;

		current.next = node;
		node.next.prev = node;
	}

	void deleteAt(size_t index)
	{
		if (index >= size || index <0)
			return;
		size--;
		Node<T>* current = first;
		if (current == nullptr)
			return;
		for (int i = 0; i < index; i++)
		{
			if(current!=nullptr)
				current = current->next;
		}
		//deleting current
		if(current->prev!=nullptr)
			current->prev->next = current->next;
		if(current->next != nullptr)
			current->next->prev = current->prev;
		current->next = current->prev = nullptr;
		delete current;
		current = nullptr;
	}

	Node<T>* getFirst()const { 
		
		return first==nullptr ? nullptr : first; 
	}
	Node<T>* getLast() const { 
		return last==nullptr?nullptr:last; 
	}
	Node<T>* getAt(size_t index) const
	{
		if (index < 0 || index >= size)
			return nullptr;
		Node<T>* temp = first;
		for (int i = 0; i < index; i++)
		{
			if (temp == nullptr)
				return nullptr;
			temp = temp->next;
		}
		return temp;
	}

	size_t getSize() { return size; }
	void countStringOccurences(const myString& s) const
	{
		int times = 0;
		Node<T>* temp = first;
		while (temp != nullptr)
		{
			if (temp->data == s)
				times++;
			temp = temp->next;
		}
		return times;
	}
	void decrementSize() { size--; }
};