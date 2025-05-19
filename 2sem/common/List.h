#pragma once

#include <stdexcept>
#include <Node.h>

template <typename T>
class List
{
private:
	Node<T>* top;
	Node<T>* bottom;
	int counter;

	Node<T>* getNode(int index)
	{
		if (index < 0 || index > counter)
		{
			throw std::out_of_range("Invalid index");
		}

		if (index < counter / 2)
		{
			Node<T>* current = top;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current;
		}
		else
		{
			Node<T>* current = bottom;
			for (int i = counter; i < index; i--)
			{
				current = current->previous;
			}
			return current;
		}
	}

public:
	/// <summary>
	/// Конструктор класса List
	/// </summary>
	List() : top(nullptr), bottom(nullptr), counter(0) {}

	/// <summary>
	/// Деструктор класса List
	/// </summary>
	~List()
	{
		clear();
	}

	/// <summary>
	/// Добавление в список элемента (с конца)
	/// </summary>
	/// <param name="value"> Добавляемое значение </param>
	void add(T value)
	{
		Node<T>* newNode = new Node<T>(value);
		if (bottom == nullptr)
		{
			top = bottom = newNode;
		}
		else
		{
			bottom->next = newNode;
			newNode->previous = bottom;
			bottom = newNode;
		}
		counter++;
	}

	/// <summary>
	/// Функция добавления в список элемента по номеру места
	/// </summary>
	/// <param name="index"> Номер по порядку (начиная с нуля) места, на которое нужно вставить элемент </param>
	/// <param name="value"> Элемент, который необходимо вставить в список </param>
	void insert(int index, T value)
	{
		if (index < 0 || index > counter)
		{
			throw std::out_of_range("Invalid index");
		}

		if (index == counter)
		{
			add(value);
			return;
		}
		Node<T>* newNode = new Node(value);
		if (index == 0)
		{
			top->previous = newNode;
			newNode->next = top;
			top = newNode;
		}
		else
		{
			Node<T>* current = getNode(index);
			current->previous->next = newNode;
			newNode->previous = current->previous;
			newNode->next = current;
		}
		counter++;
	}

	/// <summary>
	/// Функция удаления элемента по номеру
	/// </summary>
	/// <param name="index"> Номер удаляемого элемента из списка </param>
	void removeAt(int index)
	{
		if (index < 0 || index > counter)
		{
			throw std::out_of_range("Invalid index");
		}

		Node<T>* toDelete = getNode(index);
		if (index == counter - 1)
		{
			bottom = toDelete->previous;
		}
		else if (index == 0)
		{
			top = toDelete->next;
		}
		else
		{
			toDelete->previous->next = toDelete->next;
			toDelete->next->previous = toDelete->previous;
		}
		delete toDelete;
		counter--;
	}


	/// <summary>
	/// Оператор, позволяющий обращаться к элементам списка как к элементам массива: []
	/// </summary>
	/// <param name="index"> Номер элемента списка</param>
	/// <returns> Элемент, идущий по этому номеру </returns>
	T& operator[](const int index)
	{
		return getNode(index)->data;
	}

	/// <summary>
	/// Подсчет количества элементов входящих в список
	/// </summary>
	int count()
	{
		return counter;
	}

	/// <summary>
	/// Подсчет, сколько раз заданное число входит в список
	/// </summary>
	/// <param name="value"> Элемент, по которому ведется поиск в списке </param>
	int count(T value)
	{
		if (bottom == nullptr)
		{
			return 0;
		}

		int count = 0;
		Node<T>* current = top;
		for (int i = 0; i < counter; i++)
		{
			if (current->data == value)
			{
				count++;
			}
			current = current->next;
		}
		return count;
	}

	/// <summary>
	/// Функция очистки списка, используемая в деструкторе
	/// </summary>
	void clear()
	{
		Node<T>* current = top;
		while (current != nullptr)
		{
			Node<T>* next = current->next;
			delete current;
			current = next;
		}
		top = bottom = nullptr;
		counter = 0;
	}
};