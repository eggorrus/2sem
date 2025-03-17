#pragma once

#include <stdexcept>

using namespace std;

/// <summary>
/// Ниже находится описание класса "Stack", который является системой хранения данных типа "LIFO"
template <typename T>
class Stack
{
private:
	struct Node
	{
		T data;
		Node* next;

		//создан конструктор структуры Node 
		Node(const T& value) : data(value), next(nullptr) {} 
	};

	int counter;
	Node* top;

public:
	/// <summary>
	/// Конструктор для структуры Stack
	Stack() : counter(0), top(nullptr) {}
	/// <summary>
	/// Здесь представлен деструктор.
	~Stack()
	{
		clear();
	}
	/// <summary>
	/// Ниже представлен метод push. Он добавляет элемент на вершину стека.
	void push (T value)
	{
		Node* newData = new Node(value);
		newData->next = top;
		top = newData;
		++counter;
	}

	/// <summary>
	/// Далее представлен метод pop. Он извлекает и возвращает значение с вершины стека.
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
	int count()
	{
		return counter;
	}

	/// <summary>
	/// Метод clear очищает стек и применяется в деструкторе.
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