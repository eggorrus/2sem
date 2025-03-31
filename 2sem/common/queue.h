#pragma once

#include <stdexcept>

/// <summary>
/// Класс Queue, система хранения данных FIFO.
/// </summary>
template <typename T>
class Queue
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& value) : data(value), next(nullptr) {}
	};

	Node* top;
	Node* bot;
	int counter;

public:
	/// <summary>
	/// Конструктор класса Queue
	/// </summary>
	Queue() : top(nullptr), bot(nullptr), counter(0) {}

	/// <summary>
	/// Деструткор класса Queue
	/// </summary>
	~Queue()
	{
		clear();
	}

	/// <summary>
	/// Метод добавляет в очередь новый элемент
	/// </summary>
	/// <param name="value">Значение которое нужно поместить в очередь</param>
	void queue(T value)
	{
		Node* newData = new Node(value);
		if (bot != nullptr)
		{
			bot->next = newData;
			bot = newData;
		}
		else
		{
			top = newData;
			bot = newData;
		}
		counter++;
	}

	/// <summary>
	/// Метод извлекает верхний элемент очереди
	/// </summary>
	T unqueue()
	{
		if (top != nullptr)
		{
			T outValue = top->data;
			Node* temp = top;
			top = top->next;
			delete temp;
			--counter;
			return outValue;
		}
		else
		{
			throw std::out_of_range("Queue is empty");
		}
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
			Node* temp = top;
			top = top->next;
			delete temp;
		}
		counter = 0;
	}
};