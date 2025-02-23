#pragma once

#include <stdexcept>
#include <string>

using namespace std;

/// <summary>
/// Ниже находится описание класса "Stack", который является системой хранения данных типа "LIFO"
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

		Node(const T& value) : data(value), next(nullptr) {} //создан конструктор структуры Node - created constructor of struct Node
	};

	int counter;
	Node* top;

public:
	/// <summary>
	/// Конструктор для структуры Stack
	/// Constructor for Stack structure
	/// </summary>
	Stack() : counter(0), top(nullptr) {}
	/// <summary>
	/// Здесь представлен деструктор.
	/// Here is destructor
	/// </summary>
	~Stack()
	{
		clear();
	}
	/// <summary>
	/// Ниже представлен метод push. Он добавляет элемент на вершину стека.
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
	/// Далее представлен метод pop. Он извлекает и возвращает значение с вершины стека.
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
	/// Метод peek возвращает значение элемента, находящегося на вершине.
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
	/// Метод count возвращает количество элементов стека.
	/// The count method returns the number of stack elements
	/// </summary>
	/// <returns></returns>

	int count()
	{
		return counter;
	}

	/// <summary>
	/// Метод clear очищает стек и применяется в деструкторе.
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