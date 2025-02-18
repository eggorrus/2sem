#pragma once

template <typename T>

class Stack
{
private:
	struct Node
	{
		T data;
		Node* next;
	};
	Node* top = nullptr;
	int size = 0;

public:
	void push(const T& value)
	{
		Node* newData = new Node();
		newData->data = value;
		newData->next = top;
		top = newData;
		++size;
	}

	T pop()
	{
		if (top != nullptr)
		{
			T topValue = top->data;
			top = top->next;
			--size;
			return topValue;
		}
		else
		{
			std::cerr << "Stack is empty\n";
		}
	}

	T peek()
	{
		if (top != nullptr)
		{
			return top->data;
		}
		else
		{
			std::cerr << "Stack is empty\n";
		}
	}

	int count()
	{
		return size;
	}

	void clear()
	{
		while (top != nullptr)
		{
			Node* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}
};