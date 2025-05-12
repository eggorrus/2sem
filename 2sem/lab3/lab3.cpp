#include <iostream>
#include <CycleList.h>

using namespace std;

void showMenu()
{
	cout << "Список команд:\n 1-Вставка элемента в конец списка; \n 2-Вставка элемента по заданному номеру \n";
	cout << " 3-Удаление элемента по номеру \n 4-Вывод элемента по номеру \n 5-Подсчет количества элементов в очереди\n";
	cout << " 6-Подсчет количества вхождений в очередь заданного элемента\n 7-Вставка перед всеми отрицтаельными элементами элемента со значением 1\n 8-Удаление из очереди всех отрицательных элементов\n";
	cout << " 9-Вывод текущего состояния списка\n 0-конец работы программы\n";
}

void insertOneBeforeNegatives(CycleList<int>* list)
{
	Node<int>* current = list->returnBeginning();
	for (int i = 0; i < list->count(); i++)
	{
		if (current->data < 0)
		{
			list->insert(i, 1);
			i++;
		}
		current = current->next;
	}
}

void removeNegatives(CycleList<int>* list)
{
	Node<int>* current = list->returnBeginning();
	for (int i = 0; i < list->count(); i++)
	{
		if (current->data < 0)
		{
			list->removeAt(i);
			i--;
		}
		current = current->next;
	}
}

void outputList(CycleList<int>* list)
{
	int sizeOfList = list->count();
	Node<int>* current = list->returnBeginning();
	for (int i = 0; i < list->count(); i++)
	{
		if (i != sizeOfList - 1)
		{
			cout << current->data << " ";
		}
		else
		{
			cout << current->data << endl;
		}
		current = current->next;
	}
}

int main()
{
	setlocale(LC_ALL, "");
	int command;
	CycleList<int> list;
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
				int inputValue;
				cout << "Введите элемент" << endl;
				cin >> inputValue;
				list.add(inputValue);
				break;
			}

			case 2:
			{
				int numberOfElement;
				int inputValue;
				cout << "Введите значение элемента" << endl;
				cin >> inputValue;
				cout << "Введите номер позиции, на которую его необходимо вставить (отсчет от нуля)" << endl;
				cin >> numberOfElement;
				list.insert(numberOfElement, inputValue);
				break;
			}

			case 3:
			{
				int numberOfElement;
				cout << "Введите номер элемента " << endl;
				cin >> numberOfElement;
				list.removeAt(numberOfElement);
				break;
			}

			case 4:
			{
				int numberOfElement;
				cout << "Введите номер элемента" << endl;
				cin >> numberOfElement;
				if (numberOfElement <= list.count() && numberOfElement>0)
				{
					cout << "Элемент #" << numberOfElement << ": " << list.operator[](numberOfElement) << endl;
				}
				else
				{
					cout << "Некорректный номер элемента!" << endl;
				}
				break;
			}

			case 5:
			{
				cout << "В списке " << list.count() << " элементов\n" << endl;
				break;
			}

			case 6:
			{
				int element;
				cout << "Введите элемент" << endl;
				cin >> element;
				cout << "Элемент " << element << " встречается столько раз:" << list.count(element);
				break;
			}

			case 7:
			{
				
				insertOneBeforeNegatives(&list);
				break;
			}

			case 8:
			{
				removeNegatives(&list);
				break;
			}

			case 9:
			{
				cout << "Текущее состояние списка:" << endl;
				outputList(&list);
			}

			default:
			{
				cout << "Неверная команда!" << endl;
			}
			}
		}
		catch (const std::exception& error)
		{
			cout << error.what() << endl;
			list.clear();
		}
		showMenu();
		cin >> command;
	}
}