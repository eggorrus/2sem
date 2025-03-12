#include <iostream>
#include <stack.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	int inputValue;
	Stack<int> myStack;
	cout << "Введите числа" << endl;
	cin >> inputValue;
	while (inputValue != 0)
	{
		myStack.push(inputValue);
		cin >> inputValue;
	}
	cout << "Положительные числа в обратном порядке:" << endl;
	while(myStack.count()>0)
	{
		int currentValue = myStack.pop();
		if (currentValue > 0)
		{
			cout << currentValue << endl;
		}
	}
}