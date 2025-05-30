#include <iostream>
#include <string>
#include <dictionary.h>

using namespace std;

int hashFunction(string key)
{
    int hash = 0;
    for (char ch : key)
    {
        hash += static_cast<int>(ch);
    }
    return hash;
}

void showMenu()
{
    cout << "Меню:" << endl;
    cout << "1. Добавить элемент" << endl;
    cout << "2. Удалить элемент" << endl;
    cout << "3. Получить значение по ключу" << endl;
    cout << "4. Попробовать получить значение (TryGetValue)" << endl;
    cout << "5. Показать все ключи" << endl;
    cout << "6. Показать все значения" << endl;
    cout << "7. Показать все пары ключ-значение" << endl;
    cout << "8. Очистить словарь" << endl;
    cout << "0. Окончание работы программы" << endl;
    cout << "Введите команду: " << endl;
}

int main()
{
    setlocale(LC_ALL, "");
    Dictionary<string, string> dict(hashFunction);
    int choice;
    string key, value;
    showMenu();
    cin >> choice;
    while (choice != 0)
    {
        try
        {
            switch (choice)
            {
            case 1:
            {
                cout << "Введите ключ: " <<endl;
                cin >> key;
                cout << "Введите значение: " << endl;
                cin >> value;
                dict.add(key, value);
                break;
            }

            case 2:
            {
                cout << "Введите ключ для удаления: " << endl;
                cin >> key;
                dict.remove(key);
                break;
            }

            case 3:
            {
                cout << "Введите ключ: ";
                cin >> key;
                try
                {
                    cout << "Значение: " << dict[key] << endl;
                }
                catch (exception& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }

            case 4:
            {
                cout << "Введите ключ: ";
                cin >> key;
                if (dict.TryGetValue(key, value))
                {
                    cout << "Найдено: " << value << endl;
                }
                else
                {
                    cout << "Ключ не найден." << endl;
                }
                break;
            }

            case 5:
            {
                List<string>* keys = dict.GetKeys();
                cout << "Ключи:" << endl;
                for (int i = 0; i < keys->count(); i++)
                {
                    cout << keys->operator[](i) << endl;
                }
                delete keys;
                break;
            }

            case 6:
            {
                List<string>* values = dict.GetValues();
                cout << "Значения: " << endl;
                for (int i = 0; i < values->count(); i++)
                {
                    cout << values->operator[](i) << endl;
                }
                delete values;
                break;
            }

            case 7:
            {
                List<Pair<string, string>>* items = dict.ToList();
                cout << "Пары:" << endl;
                for (int i = 0; i < items->count(); i++)
                {
                    Pair<string, string> p = items->operator[](i);
                    cout << p.key << " => " << p.value << endl;
                }
                delete items;
                break;
            }

            case 8:
            {
                dict.clear();
                cout << "Словарь очищен." << endl;
                break;
            }

            default:
            {
                cout << "Некорректная команда!" << endl;
            }
            }
        }
        catch (const std::exception& error)
        {
            cout << error.what() << endl;
            dict.clear();
        }
        showMenu();
        cin >> choice;
    }
}
