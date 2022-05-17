#include <iostream>

using namespace std;

void selecSort(int list[], int size)
{
    int min  = 0;

    for (int i = 0; i < size -1; i++)
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

void bubbleSort(int list[], int size)
{
    
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (list[j] > list[j + 1])
            {
                int temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

void shellSort(int list[], int size)
{
    for (int gap = size/2; gap > 0; gap = gap / 2)
    {
        
        for (int i = gap; i < size; i = i + 1)
        {
            int temp = list[i];

            int j;
            for (j = i; j >= gap && list[j - gap] > temp; j = j - gap)
                list[j] = list[j - gap];

            list[j] = temp;
        }
    }
}

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