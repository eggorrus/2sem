﻿#include <iostream>
#include <queue.h>

using namespace std;

Queue<int> queue;

void showMenu()
{
	cout << "Выберите команду:\n 1 - вставка перед каждым отрицательным элементом очереди элемента со значением 1\n";
	cout << " 2 - удаление из очереди всех отрицательных элементов\n 3 - Подсчет количества вхождений элемента в очередь\n";
	cout << " 4 - Добавить элемент в очередь\n 5 - Извлечь из очереди первый элемент\n 6 - Возврат количества элементов в очереди\n";
	cout << " 7 - Вывод текущего состояния очереди\n 0 - конец работы программы ";
}

void inputElement()
{
	int inputValue;
	cout << "Введите элемент очереди" << endl;
	cin >> inputValue;
	queue.queue(inputValue);
}

void insertOneBeforeNegatives()
{
	int size = queue.count();
	for (int i = 0; i < size; i++)
	{
		int value = queue.unqueue();
		if (value < 0)
		{
			queue.queue(1);
		}
		queue.queue(value);
	}
}

void removeNegatives()
{
	int size = queue.count();
	int value;
	for (int i = 0; i < size; i++)
	{
		value = queue.unqueue();
		if (value > 0)
		{
			queue.queue(value);
		}
	}
}

int countNumberOfEntries(int target)
{
	int size = queue.count();
	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		int temp = queue.unqueue();
		if (temp == target)
		{
			counter++;
		}
		queue.queue(temp);
	}
	return counter;
}

void showQueue()
{
	int size = queue.count();
	if (queue.count() == 0)
	{
		cout << "Очередь пуста\n";
	}
	else
	{
		cout << "Текущая очередь: ";
		for (int i = 0; i < size; i++)
		{
			int value = queue.unqueue();
			if (i != size - 1)
			{
				cout << value << " ";
			}
			else
			{
				cout << value << endl;
			}
			queue.queue(value);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");
	int command;
	showMenu();
	cin >> command;
	while (command != 0)
	{
		try
		{
			switch (command)
			{
			case 1:
			{
				insertOneBeforeNegatives();
				break;
			}

			case 2:
			{
				removeNegatives();
				break;
			}

			case 3:
			{
				int target;
				cout << "Введите элемент" << endl;
				cin >> target;
				cout << "Элемент " << target << "встречается " << countNumberOfEntries(target) << "раз(а)" << endl;
				break;
			}

			case 4:
			{
				inputElement();
				break;
			}

			case 5:
			{
				if (queue.count() > 0)
				{
					cout << "Первый элемент в очереди: " << queue.unqueue() << endl;
				}

				else
				{
					cout << "Очередь пуста\n";
				}
				break;
			}

			case 6:
			{
				cout << "Текущее количество элементов в очереди: " << queue.count() << endl;
				break;
			}

			case 7:
			{
				showQueue();
				break;
			}

			default:
			{
				cout << "Неверная команда!\n";
				break;
			}
			}
		}
		catch(const std::exception& error)
		{
			cout << "" << error.what() << endl;
			queue.clear();
		}
		showMenu();
		cin >> command;
	}
}