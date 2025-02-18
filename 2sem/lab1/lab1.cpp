#include <iostream>
#include <stack.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	int toStackValue;
	Stack<int> myStack;
	cout << "Введите числа" << endl;
	cin >> toStackValue;
	while (toStackValue != 0)
	{
		myStack.push(toStackValue);
		cin >> toStackValue;
	}
	int currentValue;
	int sizeOfStack = myStack.count();
	cout << "Положительные числа в обратном порядке:" << endl;
	for (int i = 0; i < sizeOfStack; i++)
	{
		currentValue = myStack.pop();
		if (currentValue > 0)
		{
			cout << currentValue << endl;
		}
	}
}