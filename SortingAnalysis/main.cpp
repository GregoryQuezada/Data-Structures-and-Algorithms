#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

// Implementation of selection sort
void selecSort(int list[], int size)
{
	int min = 0;

	for (int i = 0; i < size - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (list[j] < list[min])
				min = j;
		}

		int temp = list[min];
		list[min] = list[i];
		list[i] = temp;
	}
}

// Implementation of bubble sort
void bubbleSort(int list[], int size)
{

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (list[j] > list[j + 1])
			{
				int temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

// Implementation of heapify, needed for heap sort
void heapify(int list[], int size, int i)
{
	int greatest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && list[left] > list[greatest])
		greatest = left;

	if (right < size && list[right] > list[greatest])
		greatest = right;

	if (greatest != i)
	{
		int temp = list[i];
		list[i] = list[greatest];
		list[greatest] = temp;

		heapify(list, size, greatest);
	}
}

// Implementation of heap sort
void heapSort(int list[], int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(list, size, i);

	for (int i = size - 1; i >= 0; i--)
	{
		int temp = list[0];
		list[0] = list[i];
		list[i] = temp;
		heapify(list, i, 0);
	}
}

// disregard, helper function for file creation
void populateFile(int count, std::string const& file)
{
	std::ofstream myfile(file);
	int random_integer = 0;
	if (!myfile)
	{
		// Deal with error.
		return;
	}

	for (int index = 0; index < count; index++)
	{
		random_integer = (rand() % 100000) + 1;
		myfile << random_integer << "\n";
	}
}

// disregard, helper function for file creation
void writeFile(int count, std::string const& file, int list[])
{
	std::ofstream myfile(file);
	int random_integer = 0;
	if (!myfile)
	{
		// Deal with error.
		return;
	}

	for (int index = 0; index < count; index++)
	{
		myfile << list[index] << "\n";
	}
}

// disregard, helper function for file creation
void readFile(string const& file, int list[])
{
	ifstream myfile(file);
	if (!myfile)
		return;

	int number;
	int index = 0;
	while (myfile >> number)
	{
		list[index] = number;
		index++;
	}
	
}

// I commented out the main function as the program won't compile unless you have my input files, which I'm not supposed to turn in. 
void main()
{

	/*srand(time(NULL));

	int list[10000] = { };

	std::string file("rand100.txt");
	readFile(file, list);


	clock_t start, finish;
	start = clock();
	selecSort(list, 100000);
	finish = clock();
	cout << "Time for selection sort (seconds): " << ((float)(finish - start)) / (CLOCKS_PER_SEC / 1000) << "\n";*/

	
}