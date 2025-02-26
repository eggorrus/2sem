#include <iostream>
#include <queue.h>

using namespace std;

void insertNegatives(Queue<int> queue)
{
	int temp;
	for (int i = 0; i < queue.count(); i++)
	{
		temp = queue.unqueue();
		if (temp < 0)
		{
			queue.queue(1);
			i++;
		}
		queue.queue(temp);
	}
}

void deleteNegatives(Queue<int> queue)
{
	int temp;
	for (int i = 0; i < queue.count(); i++)
	{
		temp = queue.unqueue();
		if (temp >= 0)
		{
			queue.queue(temp);
		}
		else
		{
			i--;
		}
	}
}

int countOccurences(Queue<int> queue, int value)
{
	int quantity, temp, sizeOfQueue;
	sizeOfQueue = queue.count();
	quantity = 0;
	for (int i = 0; i < sizeOfQueue; i++)
	{
		temp = queue.unqueue();
		if (value == temp)
		{
			quantity++;
		}
		queue.queue(temp);
	}
	return quantity;
}

void printQueue(Queue<int> queue)
{
	int sizeOfQueue = queue.count();
	int temp;
	for (int i = 0; i < sizeOfQueue; i++)
	{
		temp = queue.unqueue();
		if (i != sizeOfQueue - 1)
		{
			cout << temp << " ";
		}
		else
		{
			cout << temp << endl;
		}
		queue.queue(temp);
	}
}

int main()
{
	setlocale(LC_ALL, "");
	Queue<int> myQueue;
	int var;
	bool isRunning;
	isRunning = true;
	while (isRunning)
	{
		cin >> var;
		switch (var)
		{
		case 1:
			int value;
			cin >> value;
			myQueue.queue(value);
			break;

		case 2:
			cout << "" << myQueue.unqueue() << endl;
			break;

		case 3:
			cout << "" << myQueue.count() << endl;
			break;

		case 4:
			insertNegatives(myQueue);
			cout << "" << endl;
			break;

		case 5:
			deleteNegatives(myQueue);
			cout << "" << endl;
			break;

		case 6: 
			int variable, result;
			cin >> value;
			result = countOccurences(myQueue, variable);
			cout << "" << variable << "" << result << endl;
			break;

		case 7:
			cout << "";
			printQueue(myQueue);
			break;

		case 8:
			isRunning = false;
			break;
		
		default:
			cout << "" << endl;
			break;
		}
	}
}