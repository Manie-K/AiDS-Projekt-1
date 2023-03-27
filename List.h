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
		Node<T>* current = first;
		Node<T>* next = nullptr;

		while (current != nullptr)
		{
			next = current->next;
			//delete current;
			current = next;
		}
	}

	void display() const
	{
		Node<T>* current = first;
		int i = 0;
		cout << endl;
		while (current != nullptr)
		{
			cout << ++i << " " << current << endl;
			current = current->next;
		}
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
		size--;
		first = first->next;
		delete first->prev;
		first->prev = nullptr;
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
		size--;
		last = last->prev;
		delete last->next;
		last->next = nullptr;
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

	void deleteAfter(size_t index)
	{
		if (index >= size - 1)
			return;
		size--;
		Node<T>* current = first;
		for (int i = 0; i < index; i++)
		{
			current = current.next;
		}
		//deleting after current
		current.prev.next = current.next;
		current.next.prev = current.prev;
		current.next = current.prev = nullptr;
		delete current;
	}

	Node<T>* getFirst()const { return first; }
	Node<T>* getLast() const { return last; }
	Node<T>* getAfter(size_t index) const
	{
		if (index < 0 || index >= size)
			return nullptr;
		Node<T>* temp = first;
		for (int i = 0; i < index; i++)
			temp = temp->next;
		return temp;
	}

	int getSize() { return size; }
	void incrementSize(){size++;}
	void decrementSize() { size--; }
};