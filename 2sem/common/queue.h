#pragma once

#include <stdexcept>

using namespace std;

template <typename T>

class Queue
{
private:

	struct Node
	{
		T data;
		Node* next;
		Node* prev;

		Node(const T& value) : data(value), next(nullptr) {}
	};

	int counter;
	Node* top;
	Node* bot;

public:

	Queue() : counter(0), top(nullptr), bot(nullptr) {}

	~Queue
	{
		clear();
	}

	void queue(const T& value)
	{
		Node* newData = new Node(value);
		newData->data = value;
		newData->prev = bot;
		bot->next = newData;
		bot = newData;
		if (top == nullptr)
		{
			top = newData;
		}
		counter++;
	}

	T unqueue()
	{
		if (bot == nullptr)
		{
			throw out_of_range("Queue is empty!");
		}
		else
		{
			T value = top->data;
			Node* temp = top;
			top = top->next;
			delete temp;
			--counter;
			return value;
		}
	}

	int count()
	{
		return counter;
	}

	void clear()
	{
		while (top != nullptr)
		{
			Node* temp = top;
			top = top->next;
			delete temp;
		}
		counter = 0;
	}
};