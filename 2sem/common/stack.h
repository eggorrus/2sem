#pragma once

#include <stdexcept>
#include <string>

using namespace std;

template <typename T>

/// <summary>
/// ���� ��������� �������� ������ "Stack", ������� �������� �������� �������� ������ ���� "LIFO"
/// Description of class "Stack" which is data storage "LIFO" system is below.
/// </summary>
class Stack
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	/// <summary>
	/// ���������� � ��������� ����� ��������� �� ������� �����, �� ��������� ���������� nullptr, � ����� ������ ������������� ����������, ���������� �� ������ �����.
	/// In the public part, we use a pointer to the top of the stack, which is nullptr by default, and also enter an integer variable responsible for the stack size.
	/// </summary>
	Node* top = nullptr;
	int size = 0;
	/// <summary>
	/// ����� ����������� ����������.
	/// Here is destructor
	/// </summary>
	~Stack()
	{
		clear();
	}
	/// <summary>
	/// ����� ������������ ��������� ������ ��� ������ �� ������:
	/// void push(T)* - ��������� ������� �� ������� �����
	/// T pop() * -��������� ������� � ������� ����� � ���������� ��� ��������
	/// T peek() * -���������� ������� ����������� �� ������� �����
	/// int count() * -���������� ���������� ��������� � ���������
	/// void clear() * -������� ��� �������� �� ���������
	/// The following methods are presented for working with the stack:
	/// void push(T)* - adds an element to the top of the stack
	/// T pop() * -retrieves an element from the top of the stack and returns its value
	/// T peek() * -returns the element at the top of the stack
	/// int count() * -returns the number of items in the collection
	/// void clear() * -removes all items from the collection
	/// </summary>
	/// <param name="value"></param>
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
			Node* temp = top;
			top = top->next;
			delete temp;
			--size;
			return topValue;
		}
		else
		{
			throw runtime_error("Stack is empty");
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
			throw runtime_error("Stack is empty");
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