#pragma once

#include <stdexcept>
#include <Node.h>

/// <summary>
/// Класс Queue, метод организации данных FIFO.
/// </summary>
template <typename T>
class Queue
{
private:

	Node<T>* top;
	Node<T>* bottom;
	int counter;

public:
	/// <summary>
	/// Конструктор класса Queue
	/// </summary>
	Queue() : top(nullptr), bottom(nullptr), counter(0) {}

	/// <summary>
	/// Деструткор класса Queue
	/// </summary>
	~Queue()
	{
		if (counter > 0)
		{
			clear();
		}
	}

	/// <summary>
	/// Метод добавляет в очередь новый элемент
	/// </summary>
	/// <param name="value">Значение которое нужно поместить в очередь</param>
	void queue(T value)
	{
		Node<T>* newData = new Node<T>(value);
		if (bottom != nullptr)
		{
			bottom->next = newData;
			bottom = newData;
		}
		else
		{
			top = bottom = newData;
		}
		counter++;
	}

	/// <summary>
	/// Метод извлекает верхний элемент очереди
	/// </summary>
	T unqueue()
	{
		if (top == nullptr || counter <= 0)  
		{
			throw std::out_of_range("Queue is empty");
		}
		T outValue = top->data;
		Node<T>* temp = top;
		top = top->next;
		if (top == nullptr)
		{
			bottom = nullptr;
		}
		delete temp;
		--counter;
		return outValue;
	}

	/// <summary>
	/// Вывод текущего количества элементов в очереди
	/// </summary>
	int count()
	{
		return counter;
	}

	/// <summary>
	/// Функция, необходимая для деструктора. Очищает очередь.
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
		bottom = nullptr;
	}
};