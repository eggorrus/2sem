#include <iostream>
#include <List.h>
#include <string>
#include <windows.h>

using namespace std;

struct Сity
{
	string name;
	string region;
	int population;
};

struct Region
{
	string name;
	int population;
};

void getInfoToList(List<Сity>* list, string name, string region, int population)
{
	Сity newCity;
	newCity.population = population;
	newCity.region = region;
	newCity.name = name;
	list->add(newCity);
}

void deleteCity(List<Сity>* list, string name)
{
	for (int i = 0; i < list->count(); i++)
	{
		if ((*list)[i].name == name)
		{
			list->removeAt(i);
			break;
		}
	}
}

List<Region>* findRegions(List<Сity>* list)
{
	List<Region>* regions = new List<Region>();
	for (int i = 0; i < list->count(); i++)
	{
		string regionName = (*list)[i].region;
		int population = (*list)[i].population;
		bool found = false;

		for (int j = 0; j < regions->count(); j++)
		{
			if ((*regions)[j].name == regionName)
			{
				(*regions)[j].population += population;
				found = true;
				break;
			}
		}

		if (!found)
		{
			Region newRegion;
			newRegion.name = regionName;
			newRegion.population = population;
			regions->add(newRegion);
		}
	}
	return regions;
}

List<Region>* sortRegions(List<Сity>* list)
{
	List<Region>* regions = findRegions(list);

	for (int i = 0; i < regions->count() - 1; i++)
	{
		for (int j = 0; j < regions->count() - 1 + i; j++)
		{
			if ((*regions)[j].population < (*regions)[j + 1].population)
			{
				Region temp = (*regions)[j];
				(*regions)[j] = (*regions)[j + 1];
				(*regions)[j + 1] = temp;
			}
		}
	}

	return regions;
}

void showRegionsWithPopulation(List<Region>* regions)
{
	for (int i = 0; i < regions->count(); i++)
	{
		cout << i+1 << ")" << (*regions)[i].name << " : население "  << (*regions)[i].population << endl;
	}
}

void showCities(List<Сity>* cities)
{
	for (int i = 0; i < cities->count(); i++)
	{
		cout << (*cities)[i].name << " " << (*cities)[i].region << " " << (*cities)[i].population << endl;
	}
}

void showMenu()
{
	cout << "Список команд:" << endl;
	cout << "1 - Ввести информацию о городе;" << endl;
	cout << "2 - Удалить информацию о городе;" << endl;
	cout << "3 - Вывести регионы по убыванию суммарной численности городского населения;" << endl;
	cout << "4 - Удалить города какого-либо региона;" << endl;
	cout << "5 - Подсчитать, сколько всего городов в списке;" << endl;
	cout << "6 - Вывести неупорядоченный список;" << endl;
	cout << "7 - Подсчет кол-ва одноименных с введенным городов;" << endl;
	cout << "0 - Окончание работы программы." << endl;
	cout << "Введите команду: ";
}

void regionChoiceMenu(List<Region>* regions)
{
	cout << "Список регионов:" << endl;
	for (int i = 0; i < regions->count(); i++)
	{
		cout << i + 1 << ")" << (*regions)[i].name << endl;
	}
	cout << "Введите номер региона, который хотите удалить:" << endl;
}

void deleteRegion(List<Region>* regions, List<Сity>* cities, int number)
{
	if (number > regions->count() + 1 || number < 0)
	{
		cout << "Некорректный номер региона!" << endl;
		return;
	}

	for (int i = 0; i < cities->count(); i++)
	{
		if ((*cities)[i].region == (*regions)[number - 1].name)
		{
			cities->removeAt(i);
			i--;
		}
	}
}

int nameSearch(List<Сity>* cities, string name)
{
	int counter = 0;
	for (int i = 0; i < cities->count(); i++)
	{
		if ((*cities)[i].name == name)
		{
			counter++;
		}
	}
	return counter;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	List<Сity> cities;
	List<Region> regions;
	bool regionsIsSorted = false;
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
				string cityName;
				string cityRegion;
				int cityPopulation;
				cout << "Введите название города" << endl;
				cin >> cityName;
				cout << "Введите регион города" << endl;
				cin >> cityRegion;
				cout << "Введите население города" << endl;
				cin >> cityPopulation;
				getInfoToList(&cities, cityName, cityRegion, cityPopulation);
				break;
			}

			case 2:
			{
				string name;
				cout << "Введите название города" << endl;
				cin >> name;
				deleteCity(&cities, name);
				break;
			}

			case 3:
			{
				if (!regionsIsSorted)
				{
					regions = *sortRegions(&cities);
				}
				regionsIsSorted = true;
				showRegionsWithPopulation(&regions);
				break;
			}

			case 4:
			{
				if (!regionsIsSorted)
				{
					regions = *sortRegions(&cities);
					regionsIsSorted = true;
				}
				int numberOfRegion;
				regionChoiceMenu(&regions);
				cin >> numberOfRegion;
				deleteRegion(&regions, &cities, numberOfRegion);
				cout << "Города региона " << (regions)[numberOfRegion-1].name <<" успешно удалены!" << endl;
				regions.removeAt(numberOfRegion - 1);
				break;
			}

			case 5:
			{ 
				cout << "В списке " << cities.count() << " городов." << endl;
				break;
			}

			case 6:
			{
				showCities(&cities);
				break;
			}

			case 7:
			{
				cout << "Введите имя города" << endl;
				string name;
				cin >> name;
				cout << "Город с названием " << name << " встречается в списке " << nameSearch(&cities, name) << " раз." << endl;
				break;
			}
			}
		}
		catch (const std::exception& error)
		{
			cout << "" << error.what() << endl;
			cities.clear();
		}

		showMenu();
		cin >> command;
	}
}