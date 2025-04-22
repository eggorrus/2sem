#pragma once

#include <stdexcept>
#include <Node.h>

/// <summary>
/// Ниже находится описание класса "Stack", который является системой хранения данных типа "LIFO"
/// </summary>
template <typename T>
class Stack
{
private:
	int counter;
	Node<T>* top;

public:
	/// <summary>
	/// Конструктор для структуры Stack
	/// /// </summary>
	Stack() : counter(0), top(nullptr) {}

	/// <summary>
	/// Здесь представлен деструктор.
	///  </summary>
	~Stack()
	{
		clear();
	}

	/// <summary>
	/// Ниже представлен метод push. Он добавляет элемент на вершину стека.
	///  </summary>
	void push (T value)
	{
		Node<T>* newData = new Node(value);
		newData->next = top;
		top = newData;
		++counter;
	}

	/// <summary>
	/// Далее представлен метод pop. Он извлекает и возвращает значение с вершины стека.
	/// </summary>
	T pop()
	{
		if (top != nullptr)
		{
			T topValue = top->data;
			Node<T>* temp = top;
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
	/// </summary>
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
	/// </summary>
	int count()
	{
		return counter;
	}

	/// <summary>
	/// Метод clear очищает стек и применяется в деструкторе.
	/// </summary>
	void clear()
	{
		while (top != nullptr)
		{
			Node<T>* temp = top;
			top = top->next;
			delete temp;
		}
		counter = 0;
	}
};
