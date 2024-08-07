#include "rogueutil.h"
#include <stdlib.h> // for rand()
#include <time.h>
#include <iostream>

using namespace std;
using namespace rogueutil;

void draw(int*, int);
void randomizeArray(int*);
void bubbleSort(int*, int*);
void quickSort(int*, int, int, int*);
int partition(int*, int, int, int*);
void insertionSort(int*, int, int*);
void selectionSort(int[], int*);
void swap(int*, int, int);
void waitForUser(int);

#define NUM_VALUES 100
#define MAX_VALUE 25
#define DELAY 1 //delay after each new draw, in milliseconds

int main(void)
{
	int numBubSwaps = 0, numQuickSwaps = 0, numInsSwaps = 0, numSelSwaps = 0;
	hidecursor();
	int * theArray = new int[NUM_VALUES];

	srand (time(NULL));

	randomizeArray(theArray);

	setColor(WHITE);

	printXY(1, MAX_VALUE+2, "Press any key to begin...");
	anykey();
	printXY(1, MAX_VALUE+2, "                         ");

	bubbleSort(theArray, &numBubSwaps);
	waitForUser(numBubSwaps);
	randomizeArray(theArray);

	quickSort(theArray, 0, NUM_VALUES-1, &numQuickSwaps);
	waitForUser(numQuickSwaps);
	randomizeArray(theArray);

	insertionSort(theArray, NUM_VALUES, &numInsSwaps);
	waitForUser(numInsSwaps);
	randomizeArray(theArray);

	selectionSort(theArray, &numSelSwaps);
	waitForUser(numSelSwaps);

	cls();
	setColor(WHITE);

	cout<<"Number of sorts in each algorithm:"<<endl<<"Bubble sort: "<<numBubSwaps<<endl;
	cout<<"Quick sort: "<<numQuickSwaps<<endl<<"Insertion sort: "<<numInsSwaps<<endl;
	cout<<"Selection sort: "<<numSelSwaps<<endl;

	return 0;
}

void draw(int* theArray, int index)
{
	setColor(WHITE);
	for (int i = 0; i < MAX_VALUE; i++)
	{
		if (i==theArray[index])
		{
			setColor(BLACK);
		}
		printXY(index+1, MAX_VALUE-i, to_string(theArray[index]%10));
	}
	msleep(DELAY);
	return;
}

void randomizeArray(int * theArray)
{
	for (int i = 0; i < NUM_VALUES; i++)
	{
		theArray[i] = 1 +(rand() % MAX_VALUE);
		draw(theArray,i);
	}

}

void swap(int* theArray, int index1, int index2)
{
	int temp = theArray[index1];
	theArray[index1] = theArray[index2];
	theArray[index2] = temp;
	draw(theArray, index1);
	draw(theArray, index2);
}

void bubbleSort(int* theArray, int* numBubSwaps)
{
	bool swapped;
	int temp = 0;
	for (int i = 0; i < NUM_VALUES; i++)
	{
		swapped = false;
		for (int j = 0; j < NUM_VALUES - i - 1; j++)
		{
			if (theArray[j] > theArray[j+1])
			{
				swap(theArray, j, j+1);
				*numBubSwaps += 1;
				swapped = true;
			}
			//draw(theArray);
		}
		if (swapped == false)
			break;
	}

	return;
}

void quickSort(int theArray[], int low, int high, int* numQuickSwaps)
{
	if (low < high)
	{
		int p = partition(theArray, low, high, numQuickSwaps);
		quickSort(theArray, low, p-1, numQuickSwaps);
		quickSort(theArray, p+1, high, numQuickSwaps);
	}

	return;
}

int partition(int theArray[], int low, int high, int* numQuickSwaps)
{
	int pivot = theArray[high];
	int i = (low-1);
	for (int j = low; j < high; j++)
	{
		if (theArray[j] <= pivot)
		{
			i += 1;
			swap(theArray, i, j);
			*numQuickSwaps += 1;
		}
	}
	swap(theArray, i+1, high);
	*numQuickSwaps += 1;

	return (i+1);
}

void insertionSort(int* theArray, int len, int* numInsSwaps)
{
	int key;
	int j;
	for (int i = 0; i < len; i++)
	{
		key = theArray[i];
		j = i - 1;

		while (j >= 0 && theArray[j] > key)
		{
			swap(theArray, j, j+1);
			*numInsSwaps += 1;
			j--;
		}
		theArray[j+1] = key;
	}

	return;
}

void selectionSort(int theArray[], int* numSelSwaps)
{
	int min = 0;
	for (int i = 0; i < NUM_VALUES; i++)
	{
		min = i;
		for (int j = i+1; j < NUM_VALUES; j++)
		{
			if (theArray[j] < theArray[min])
				min = j;
		}
		if (min != i)
		{
			swap(theArray, i, min);
			*numSelSwaps += 1;
		}
	}
	return;
}

void waitForUser(int numSwaps)
{
	setColor(WHITE);
	string msg = "Number of swaps: " + to_string(numSwaps);
	printXY(1, MAX_VALUE+2, msg);
	printXY(1, MAX_VALUE+3, "Press any key to continue...");
	anykey();
	printXY(1, MAX_VALUE+2, "                                                                            ");
	printXY(1, MAX_VALUE+3, "                            ");
	return;
}
