#pragma once

#include <stdexcept>
#include <Node.h>

template <typename T>
class CycleList
{
private:
	Node<T>* beginning;
	Node<T>* end;
	int counter;

	Node<T>* getNode(int index)
	{
		if (index < 0 || index >= counter)
		{
			throw std::out_of_range("Invalid index")
		}
		else
		{
			Node<T>* current = beginning;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current;
		}
	}

public:
	CycleList() : beginning(nullptr), end(nullptr), counter(0) {}

	~CycleList()
	{
		clear();
	}

	void add(T element)
	{
		Node<T>* newNode = new Node<T>(element);
		if (beginning == nullptr)
		{
			beginning = newNode;
			end = newNode;
		}
		else
		{
			end->next = newNode;
			end = newNode;
		}
		counter++;
	}

	void insert(int index, T element)
	{
		Node<T>* newNode = new Node<T>(element);
		if(index < 0 || index > counter)
		{
			throw std::out_of_range("Invalid index")
		}
		else if (index == 0)
		{
			newNode->next = beginning;
			beginning = newNode;
			if (end == nullptr)
			{
				end = newNode;
			}
		}
		else if (index == counter)
		{
			end->next = newNode;
			end = newNode;
		}
		else
		{
			Node<T>* previous = getNode(index - 1);
			newNode->next = previous->next;
			previous->next = newNode;
		}
		counter++;
	}

	void removeAt(int index) 
	{
		if (index < 0 || index >= counter)
		{
			throw std::out_of_range("Invalid index");
		}
		Node<T>* toDelete;
		if (index == 0)
		{  
			toDelete = beginning;
			beginning = beginning->next;
			if (counter == 1)
			{  
				end = nullptr;
			}
		}
		else
		{
			Node<T>* previous = getNode(index - 1);
			toDelete = previous->next;
			previous->next = toDelete->next;
			if (index == counter - 1) 
			{  
				end = previous;
			}
		}
		delete toDelete;
		counter--;
	}

	T& operator[](const int index)
	{
		return getNode(index)->data;
	}

	int count()
	{
		return counter;
	}

	int count(T& value)
	{
		int count = 0;
		Node<T>* current = beginning;
		for (int i = 0; i < counter; i++)
		{
			if (current->data == value)
			{
				count++
			}
			current = current->next;
		}
		return count;
	}

	void clear()
	{
		while (top != nullptr)
		{
			Node<T>* temp = top;
			top = top->next;
			delete temp;
		}
		counter = 0;
		delete end;
	}
};