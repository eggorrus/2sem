#include <CycleList.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <iomanip>

using namespace std;

const int marksCount = 5;

class Students
{
private:
	string fullName;
	int groupNumber;
	int marks[marksCount];
	double scholarshipSize;
	string additionalInfo;
public:
	Students() : fullName(""), groupNumber(0), scholarshipSize(0), additionalInfo("")
	{
		fill_n(marks, marksCount, 0);
	}

	Students(string fullName, int group, const int* marksPtr, double scholarship, string exInfo) :
		fullName(fullName), groupNumber(group), scholarshipSize(scholarship), additionalInfo(exInfo)
	{
		if (marksPtr) 
		{
			copy(marksPtr, marksPtr + marksCount, marks);
		}
	}

	string getFullName() const { return fullName; }
	int getGroupNumber() const { return groupNumber; }
	const int* getMarks() const { return marks; }
	double getScholarshipSize() const { return scholarshipSize; }
	string getAdditionalInfo() const { return additionalInfo; }

	void setFullName(const string& name) { fullName = name; }
	void setGroupNumber(int group) { groupNumber = group; }
	void setScholarshipSize(double scholarship) { scholarshipSize = scholarship; }
	void setAdditionalInfo(const string& info) { additionalInfo = info; }

	void setMarks(const int* marksPtr)
	{
		if (marksPtr) 
		{
			copy(marksPtr, marksPtr + marksCount, marks);
		}
	}

	void setMark(int index, int value)
	{
		if (index >= 0 && index < marksCount) 
		{
			marks[index] = value;
		}
	}

	bool hasNoTwos() const 
	{
		return find(begin(marks), end(marks), 2) == end(marks);
	}

	bool hasMostlyFives() const 
	{
		int countFives = count(begin(marks), end(marks), 5);
		return countFives > 2; 
	}
};

void showMenu()
{
	cout << "Список команд: " << endl;
	cout << "1 - Консольный ввод данных о потоке;" << endl;
	cout << "2 - Файловый ввод данных о потоке;" << endl;
	cout << "3 - Редактировать информацию о потоке;" << endl;
	cout << "4 - Рассчет для каждой группы количества студентов, не имеющих двоек и имеющих большинство оценок пятерки;" << endl;
	cout << "5 - Консольный вывод информации о потоке;" << endl;
	cout << "6 - Файловый вывод информации о потоке;" << endl;
	cout << "0 - Окончание работы программы. ";
}

void consoleInput(CycleList<Students>& studentFlow, int count)
{
	for (int i = 0; i < count; i++) {
		cout << "\nСтудент #" << i + 1 << endl;
		string name, info;
		int group;
		int marks[marksCount];
		double scholarship;
		if (i != 0)
		{
			cout << "Нажмите Enter" << endl;
		}
		cin.ignore(50, '\n');
		cout << "ФИО: ";
		getline(cin, name);

		cout << "Номер группы: ";
		cin >> group;

		cout << "5 оценок через пробел: ";
		for (int j = 0; j < marksCount; j++) 
		{
			cin >> marks[j];
		}

		cout << "Размер стипендии: ";
		cin >> scholarship;
		cin.ignore();

		cout << "Доп. информация: ";
		getline(cin, info);

		studentFlow.add(Students(name, group, marks, scholarship, info));
	}
}

void showEditMenu()
{
	cout << "Меню редактирования" << endl;
	cout << "1 - Добавить студента;" << endl;
	cout << "2 - Удалить студента;" << endl;
	cout << "3 - Редактировать данные студента;" << endl;
	cout << "4 - Удалить группу;" << endl;
	cout << "5 - Возвращение в главное меню." << endl;
}

void showStudentsList(CycleList<Students>& studentFlow)
{
	cout << "Список студентов: " << endl;
	for (int i = 0; i < studentFlow.count(); i++)
	{
		cout << i + 1 << ". " << studentFlow[i].getFullName() << " (Группа: " << studentFlow[i].getGroupNumber() << ")" << endl;
	}
}

const void showStudent(Students& student)
{
	cout << "Текущие данные студента:" << endl;
	cout << "1. ФИО: " << student.getFullName() << endl;
	cout << "2. Группа: " << student.getGroupNumber() << endl;
	cout << "3. Оценки: ";
	for (int i = 0; i < marksCount; i++)
	{
		cout << student.getMarks()[i] << " ";
	}
	cout << endl;
	cout << "4. Стипендия: " << student.getScholarshipSize() << endl;
	cout << "5. Доп. информация: " << student.getAdditionalInfo() << endl;
}

void editStudentData(CycleList<Students>& studentFlow)
{
	showStudentsList(studentFlow);
	cout << "Введите номер студента, данные о котором хотите изменить: " << endl;
	int number;
	cin >> number;
	if (number > 0 && number < studentFlow.count() + 1)
	{
		Students& student = studentFlow[number-1];
		showStudent(student);
		cout << "Какие данные вы хотите изменить? (0 - отмена)" << endl;
		int field;
		cin >> field;
		switch (field)
		{
		case 1:
		{
			string name;
			cout << "Введите новые ФИО" << endl;
			cin.ignore(50, '\n');
			getline(cin, name);
			student = Students(name, student.getGroupNumber(), student.getMarks(), student.getScholarshipSize(), student.getAdditionalInfo());
			break;
		}

		case 2:
		{
			cout << "Введите новый номер группы:" << endl;
			int newGroupNumber;
			cin >> newGroupNumber;
			student = Students(student.getFullName(), newGroupNumber, student.getMarks(), student.getScholarshipSize(), student.getAdditionalInfo());
			break;
		}

		case 3:
		{
			cout << "1 - Изменить все оценки\n2 - Изменить одну оценку\n> ";
			int choice;
			cin >> choice;

			if (choice == 1)
			{
				int newMarks[marksCount];
				cout << "Введите " << marksCount << " новых оценок: ";
				for (int i = 0; i < marksCount; i++) {
					cin >> newMarks[i];
				}
				student.setMarks(newMarks);
			}
			else if (choice == 2)
			{
				cout << "Введите индекс оценки (1-" << marksCount << "): ";
				int index;
				cin >> index;
				cout << "Новая оценка: ";
				int value;
				cin >> value;
				student.setMark(index - 1, value);
			}
			break;
		}

		case 4:
		{
			cout << "Введите новый размер стипендии:" << endl;
			double newScholarshipSize;
			cin >> newScholarshipSize;
			student = Students(student.getFullName(), student.getGroupNumber(), student.getMarks(), newScholarshipSize, student.getAdditionalInfo());
			break;
		}

		case 5:
		{
			cin.ignore();
			cout << "Введите новые дополнительные данные:" << endl;
			string newInfo;
			getline(cin, newInfo);
			student = Students(student.getFullName(), student.getGroupNumber(), student.getMarks(), student.getScholarshipSize(), newInfo);
			break;
		}
		case 0:
		{
			cout << "Редактирование отменено." << endl;
			break;
		}
		default:
		{
			cout << "Неверная команда!" << endl;
			break;
		}
		}
	}
}

void editFlow(CycleList<Students>& studentFlow)
{
	showEditMenu();
	int choice;
	cin >> choice;
	while (choice != 5)
	{
		switch (choice)
		{
		case 1:
		{
			consoleInput(studentFlow, 1);
			break;
		}

		case 2:
		{
			showStudentsList(studentFlow);
			cout << "Введите номер студента, данные которого нужно удалить" << endl;
			int number;
			cin >> number;
			if (number > 0 && number < studentFlow.count() + 1)
			{
				cout << "Вы действительно хотите удалить студента " << studentFlow[number - 1].getFullName() << "? (y/n): ";
				char confirm;
				cin >> confirm;

				if (confirm == 'y' || confirm == 'Y')
				{
					studentFlow.removeAt(number - 1);
					cout << "Студент успешно удален." << endl;
				}
				else
				{
					cout << "Удаление отменено." << endl;
				}
			}
			else
			{
				cout << "Неверный номер студента!" << endl;
			}
			break;
		}

		case 3:
		{
			editStudentData(studentFlow);
			break;
		}

		case 4:
		{
			showStudentsList(studentFlow);
			cout << "Какую группу вы бы хотели удалить?" << endl;
			int deleteGroup;
			cin >> deleteGroup;
			for (int i = 0; i < studentFlow.count(); i++)
			{
				if (studentFlow[i].getGroupNumber() == deleteGroup)
				{
					studentFlow.removeAt(i);
					i--;
				}
			}
			cout << "Группа #" << deleteGroup << " успешно удалена!" << endl;
			break;
		}

		default:
		{
			cout << "Неверная команда!" << endl;
			break;
		}
		}
		showEditMenu();
		cin >> choice;
	}

}

void calculateStatistics(CycleList<Students>& studentFlow) {
	if (studentFlow.count() == 0)
	{
		cout << "Список студентов пуст!" << endl;
		return;
	}

	CycleList<int> uniqueGroups;
	for (int i = 0; i < studentFlow.count(); i++)
	{
		int group = studentFlow[i].getGroupNumber();
		bool found = false;

		for (int j = 0; j < uniqueGroups.count(); j++)
		{
			if (uniqueGroups[j] == group)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			uniqueGroups.add(group);
		}
	}

	cout << "\nСтатистика по группам:\n";
	cout << "Группа\tБез двоек\tМного пятерок\n";
	cout << "---------------------------------\n";

	for (int i = 0; i < uniqueGroups.count(); i++)
	{
		int group = uniqueGroups[i];
		int noTwosCount = 0;
		int mostlyFivesCount = 0;
		for (int j = 0; j < studentFlow.count(); j++)
		{
			if (studentFlow[j].getGroupNumber() == group) 
			{
				if (studentFlow[j].hasNoTwos()) 
				{
					noTwosCount++;
				}
				if (studentFlow[j].hasMostlyFives()) 
				{
					mostlyFivesCount++;
				}
			}
		}

		cout << group << "\t" << noTwosCount << "\t\t" << mostlyFivesCount << endl;
	}
}

void fileInput(CycleList<Students>& studentFlow) 
{
	string filename;
	cout << "Введите имя файла для загрузки данных: ";
	cin >> filename;

	ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
		return;
	}

	studentFlow.clear(); 

	string line;
	while (getline(inputFile, line)) 
	{
		string name, info;
		int group;
		int marks[marksCount];
		double scholarship;

		istringstream iss(line);
		getline(iss, name, ';');
		iss >> group;
		iss.ignore(); 

		for (int i = 0; i < marksCount; i++) {
			iss >> marks[i];
			if (i < marksCount - 1)
			{
				iss.ignore();
			}
		}

		iss.ignore();
		iss >> scholarship;
		iss.ignore();
		getline(iss, info);

		studentFlow.add(Students(name, group, marks, scholarship, info));
	}

	inputFile.close();
	cout << "Данные успешно загружены из файла!" << endl;
}

void fileOutput(CycleList<Students>& studentFlow) 
{
	if (studentFlow.count() == 0) 
	{
		cout << "Нет данных для сохранения!" << endl;
		return;
	}

	string filename;
	cout << "Введите имя файла для сохранения данных: ";
	cin >> filename;

	ofstream outputFile(filename);
	if (!outputFile.is_open())
	{
		cout << "Ошибка создания файла!" << endl;
		return;
	}

	for (int i = 0; i < studentFlow.count(); i++) 
	{
		const Students& student = studentFlow[i];
		string name = student.getFullName();
		replace(name.begin(), name.end(), ';', ' ');

		string info = student.getAdditionalInfo();
		replace(info.begin(), info.end(), ';', ' ');

		outputFile << name << ";" << student.getGroupNumber() << ";";

		const int* marks = student.getMarks();
		for (int j = 0; j < marksCount; j++) 
		{
			outputFile << marks[j];
			if (j < marksCount - 1) outputFile << " ";
		}

		outputFile << ";" << fixed << setprecision(2) << student.getScholarshipSize() << ";" << info;
		if (i < studentFlow.count() - 1)
		{
			outputFile << endl;
		}
	}

	outputFile.close();
	cout << "Данные успешно сохранены в файл " << filename << "!" << endl;
}

void consoleOutput(CycleList<Students>& studentFlow) {
	if (studentFlow.count() == 0) {
		cout << "Список студентов пуст!" << endl;
		return;
	}

	// Шапка таблицы
	cout << "\n";
	cout << left << setw(53) << "ФИО"
		<< setw(10) << "Группа"
		<< setw(20) << "Оценки"
		<< setw(15) << "Стипендия"
		<< "Доп. информация" << endl;

	cout << setfill('-') << setw(113) << "-" << setfill(' ') << endl;

	for (int i = 0; i < studentFlow.count(); i++) {
		const Students& student = studentFlow[i];
		const int* marks = student.getMarks();

		string marksStr;
		for (int j = 0; j < marksCount; j++) {
			marksStr += to_string(marks[j]);
			if (j < marksCount - 1) marksStr += " ";
		}

		cout << left << setw(53) << student.getFullName()
			<< setw(10) << student.getGroupNumber()
			<< setw(20) << marksStr
			<< setw(15) << fixed << setprecision(2) << student.getScholarshipSize()
			<< student.getAdditionalInfo() << endl;
	}

	cout << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CycleList<Students> studentFlow;
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
				cout << "Введите количество студентов: " << endl;
				int count;
				cin >> count;
				consoleInput(studentFlow, count);
				break;
			}

			case 2:
			{
				fileInput(studentFlow);
				break;
			}

			case 3:
			{
				editFlow(studentFlow);
				break;
			}

			case 4:
			{
				calculateStatistics(studentFlow);
				break;
			}

			case 5:
			{
				consoleOutput(studentFlow);
				break;
			}

			case 6:
			{
				fileOutput(studentFlow);
				break;
			}

			default:
			{
				cout << "Неверная команда!" << endl;
				break;
			}
			}
		}
		catch (const std::exception& error)
		{
			cout << error.what() << endl;
			studentFlow.clear();
		}
		showMenu();
		cin >> command;
	}
}