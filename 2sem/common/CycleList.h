#pragma once

#include <stdexcept>
#include <Node.h>

template <typename T>
class CycleList
{
private:
	Node<T>* end;
	int counter;
	Node<T>* currentNode;
	int currentCount;

	Node<T>* getNode(int index)
	{
		if (index < 0 || index >= counter)
		{
			throw std::out_of_range("Invalid index");
		}
		if (currentNode == nullptr)
		{
			throw std::out_of_range("Empty list");
		}
		if (currentCount == index)
		{
			return currentNode;
		}
		if (index == counter - 1)
		{
			currentNode = end;
			currentCount = index;
		}
		else if (index == 0) 
		{
			currentNode = end->next;
			currentCount = 0;
		}
		else if (index == counter - 1)
		{
			currentNode = end;
			currentCount = counter - 1;
		}
		else 
		{
			while (currentCount < index) 
			{
				currentNode = currentNode->next;
				currentCount++;
			}
			while (currentCount > index) 
			{
				currentNode = currentNode->next; 
				currentCount++;
				if (currentCount >= counter) 
				{
					currentCount -= counter;
				}
			}
		}
		return currentNode;
	}

public:
	/// <summary>
	/// Конструктор класса CycleList
	/// </summary>
	CycleList() : end(nullptr), counter(0), currentNode(nullptr), currentCount(0) {}

	/// <summary>
	/// Деструктор класса CycleList
	/// </summary>
	~CycleList()
	{
		clear();
	}
	
	/// <summary>
	/// Метод, позволяющий получить начало списка без использования [] оператора
	/// </summary>
	/// <returns>Начало списка</returns>
	Node<T>* getHead() const
	{
		if (end == nullptr) return nullptr;
		return end->next;
	}

	/// <summary>
	/// Метод, позволяющий получить текущий элемент
	/// </summary>
	/// <returns>Текущий элемент</returns>
	Node<T>* getCurrent() const 
	{
		return currentNode;
	}

	/// <summary>
	/// Сбрасывает текущий элемент
	/// </summary>
	void resetCurrent() 
	{
		if (end != nullptr) {
			currentNode = end->next;
			currentCount = 0;
		}
	}

	/// <summary>
	/// Добавление в список элемента (с конца)
	/// </summary>
	/// <param name="element"> Добавляемое значение </param>
	void add(T element)
	{
		Node<T>* newNode = new Node<T>(element);
		if (end == nullptr)
		{
			end = newNode;
			newNode->next = end;
		}
		else
		{
			newNode->next = end->next;
			end->next = newNode;
			end = newNode;
		}
		currentNode = newNode;
		counter++;
		currentCount = counter - 1;
	}

	/// <summary>
	/// Функция добавления в список элемента по номеру места
	/// </summary>
	/// <param name="index"> Номер по порядку (начиная с нуля) места, на которое нужно вставить элемент </param>
	/// <param name="element"> Элемент, который необходимо вставить в список </param>
	void insert(int index, T element)
	{
		if(index < 0 || index > counter)
		{
			throw std::out_of_range("Invalid index");
		}
		if (index == counter)
		{
			add(element);
		}
		else
		{
			Node<T>* newNode = new Node<T>(element);
			if (index == 0)
			{
				newNode->next = end->next;
				end->next = newNode;
			}
			else
			{
				Node<T>* previous = getNode(index - 1);
				newNode->next = previous->next;
				previous->next = newNode;
			}
			counter++;
			currentNode = newNode;
		}
		currentCount = index;
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
			toDelete = end->next;
			if (counter == 1)
			{  
				end = nullptr;
				currentNode = nullptr;
				currentCount = 0;
			}
			else
			{
				end->next = toDelete->next;
				currentNode = end->next;
				currentCount = 0;
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
			if (currentCount >= index) 
			{
				currentCount--;
			}
			if (currentNode == toDelete) 
			{
				currentNode = toDelete->next;
				if (currentNode == end->next && counter > 0)
				{
					currentCount = 0;
				}
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
	int count(T value)
	{
		if (end == nullptr)
		{
			return 0;
		}

		int count = 0;
		Node<T>* current = end->next;
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
		if (end == nullptr)
		{
			return;
		}

		Node<T>* current = end->next;
		end->next = nullptr;
		while (current != nullptr)
		{
			Node<T>* toDelete = current;
			current = current->next;
			delete toDelete;
		}
		end = nullptr;
		counter = 0;
		currentNode = nullptr;
		currentCount = 0;
	}
};