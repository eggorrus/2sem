#pragma once

#include <stdexcept>
#include <string>

using namespace std;

/// <summary>
/// ���� ��������� �������� ������ "Stack", ������� �������� �������� �������� ������ ���� "LIFO"
/// Description of class "Stack" which is data storage "LIFO" system is below.
/// </summary>

template <typename T>

class Stack
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& value) : data(value), next(nullptr) {} //������ ����������� ��������� Node - created constructor of struct Node
	};

	int counter;
	Node* top;

public:
	/// <summary>
	/// ����������� ��� ��������� Stack
	/// Constructor for Stack structure
	/// </summary>
	Stack() : counter(0), top(nullptr) {}
	/// <summary>
	/// ����� ����������� ����������.
	/// Here is destructor
	/// </summary>
	~Stack()
	{
		clear();
	}
	/// <summary>
	/// ���� ����������� ����� push. �� ��������� ������� �� ������� �����.
	/// Method push is below. It adds an element on top of the Stack.
	/// </summary>
	/// <param name="value"></param>
	void push(const T& value)
	{
		Node* newData = new Node(value);
		newData->data = value;
		newData->next = top;
		top = newData;
		++counter;
	}

	/// <summary>
	/// ����� ����������� ����� pop. �� ��������� � ���������� �������� � ������� �����.
	/// The following is the pop method. It extracts and returns a value from the top of the stack.
	/// </summary>
	/// <returns></returns>

	T pop()
	{
		if (top != nullptr)
		{
			T topValue = top->data;
			Node* temp = top;
			top = top->next;
			delete temp;
			--counter;
			return topValue;
		}
		else
		{
			throw out_of_range("Stack is empty");
		}
	}

	/// <summary>
	/// ����� peek ���������� �������� ��������, ������������ �� �������.
	/// The peek method returns the value of the element located at the top
	/// </summary>
	/// <returns></returns>

	T peek()
	{
		if (top != nullptr)
		{
			return top->data;
		}
		else
		{
			throw out_of_range("Stack is empty");
		}
	}

	/// <summary>
	/// ����� count ���������� ���������� ��������� �����.
	/// The count method returns the number of stack elements
	/// </summary>
	/// <returns></returns>

	int count()
	{
		return counter;
	}

	/// <summary>
	/// ����� clear ������� ���� � ����������� � �����������.
	/// The clear method clears the stack and is applied in the destructor.
	/// </summary>

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