#include <iostream>
#include <queue.h>

using namespace std;

void showMenu()
{
	cout << "Выберите команду:\n 1 - вставка перед каждым отрицательным элементом очереди элемента со значением 1\n";
	cout << " 2 - удаление из очереди всех отрицательных элементов\n 3 - Подсчет количества вхождений элемента в очередь\n";
	cout << " 4 - Вывод текущего состояния очереди\n 0 - конец работы программы ";
}

int main()
{
	setlocale(LC_ALL, "");
	cout << "Введите элементы очереди (признак окончания последовательности - 0)" << endl;
	Queue<int> queue;
	int inputValue;
	cin >> inputValue;
	while (inputValue != 0)
	{
		queue.queue(inputValue);
		cin >> inputValue;
	}
	int command;
	showMenu();
	cin >> command;
	while (command != 0)
	{
		switch (command)
		{
		case 1:
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
			break;
		}

		case 2:
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
			break;
		}

		case 3:
		{
			int size = queue.count();
			int counter = 0;
			int target;
			cout << "Введите элемент" << endl;
			cin >> target;
			for (int i = 0; i < size; i++)
			{
				int temp = queue.unqueue();
				if (temp == target)
				{
					counter++;
				}
				queue.queue(temp);
			}
			cout << "Элемент " << target << " встречается " << counter << " раз(a)." << endl;
			break;
		}

		case 4:
		{
			int size = queue.count();
			if (size == 0)
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
			break;
		}

		default:
		{
			cout << "Неверная команда!\n";
			break;
		}
		}
		showMenu();
		cin >> command;
	}
}