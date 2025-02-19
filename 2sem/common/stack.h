#pragma once

#include <stdexcept>
#include <string>

using namespace std;

template <typename T>

/// <summary>
/// Ниже находится описание класса "Stack", который является системой хранения данных типа "LIFO"
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
	/// Используем в публичной части указатель на вершину стека, по умолчанию являющийся nullptr, а также вводим целочисленную переменную, отвечающую за размер стека.
	/// In the public part, we use a pointer to the top of the stack, which is nullptr by default, and also enter an integer variable responsible for the stack size.
	/// </summary>
	Node* top = nullptr;
	int size = 0;
	/// <summary>
	/// Здесь представлен деструктор.
	/// Here is destructor
	/// </summary>
	~Stack()
	{
		clear();
	}
	/// <summary>
	/// Далее представлены следующие методы для работы со стеком:
	/// void push(T)* - добавляет элемент на вершину стека
	/// T pop() * -извлекает элемент с вершины стека и возвращает его значение
	/// T peek() * -возвращает элемент находящийся на вершине стека
	/// int count() * -возвращает количество элементов в коллекции
	/// void clear() * -удаляет все элементы из коллекции
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