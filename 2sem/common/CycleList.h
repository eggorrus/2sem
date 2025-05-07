#pragma once

#include <stdexcept>
#include <Node.h>

template <typename T>
class CycleList
{
private:
	Node<T>* beginning;
	Node<T>* end;
	int counter;

	Node<T>* getNode(int index)
	{
		if (index < 0 || index >= counter)
		{
			throw std::out_of_range("Invalid index");
		}
		else
		{
			Node<T>* current = beginning;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			return current;
		}
	}

public:
	/// <summary>
	/// Конструктор класса CycleList
	/// </summary>
	CycleList() : beginning(nullptr), end(nullptr), counter(0) {}

	/// <summary>
	/// Деструктор класса CycleList
	/// </summary>
	~CycleList()
	{
		clear();
	}

	/// <summary>
	/// Добавление в список элемента (с конца)
	/// </summary>
	/// <param name="element"> Добавляемое значение </param>
	void add(T element)
	{
		Node<T>* newNode = new Node<T>(element);
		if (beginning == nullptr)
		{
			beginning = newNode;
			end = newNode;
		}
		else
		{
			end->next = newNode;
			end = newNode;
		}
		counter++;
	}

	/// <summary>
	/// Функция добавления в список элемента по номеру места
	/// </summary>
	/// <param name="index"> Номер по порядку (начиная с нуля) места, на которое нужно вставить элемент </param>
	/// <param name="element"> Элемент, который необходимо вставить в список </param>
	void insert(int index, T element)
	{
		Node<T>* newNode = new Node<T>(element);
		if(index < 0 || index > counter)
		{
			throw std::out_of_range("Invalid index");
		}
		else if (index == 0)
		{
			newNode->next = beginning;
			beginning = newNode;
			if (end == nullptr)
			{
				end = newNode;
			}
		}
		else if (index == counter)
		{
			end->next = newNode;
			end = newNode;
		}
		else
		{
			Node<T>* previous = getNode(index - 1);
			newNode->next = previous->next;
			previous->next = newNode;
		}
		counter++;
	}

	/// <summary>
	/// Функция удаления элемента по номеру
	/// </summary>
	/// <param name="index"> Номер удаляемого элемента из списка </param>
	void removeAt(int index) 
	{
		if (index < 0 || index >= counter)
		{
			throw std::out_of_range("Invalid index");
		}
		Node<T>* toDelete;
		if (index == 0)
		{  
			toDelete = beginning;
			beginning = beginning->next;
			if (counter == 1)
			{  
				end = nullptr;
			}
		}
		else
		{
			Node<T>* previous = getNode(index - 1);
			toDelete = previous->next;
			previous->next = toDelete->next;
			if (index == counter - 1) 
			{  
				end = previous;
			}
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
	int count(T& value)
	{
		int count = 0;
		Node<T>* current = beginning;
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
	/// Позволяет обращаться к началу списка
	/// </summary>
	/// <returns> Указатель на первый элемент списка </returns>
	Node<T>* returnBeginning()
	{
		return beginning;
	}

	/// <summary>
	/// Функция очистки списка, используемая в деструкторе
	/// </summary>
	void clear()
	{
		while (beginning != nullptr)
		{
			Node<T>* temp = beginning;
			beginning = beginning->next;
			delete temp;
		}
		counter = 0;
		delete end;
	}
};