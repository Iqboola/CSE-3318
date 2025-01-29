#include <stdio.h>

void insertionSort(int array[], int length);
int binarySearch(int array[], int element, int leftIndex, int rightIndex);

int main()
{
    int array[] = {9, 5, 13, 3, 8, 7, 2, 12, 6, 10, 4, 11, 1};
    //sorted array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}
    int length = sizeof(array) / sizeof(array[0]);

    insertionSort(array, length);

    printf("Insertion Sort:\n");
    for (int i = 0; i < length; i++)
    {
        printf("array[%d] = %d\n", i, array[i]);
    }

    int findIndex;

    printf("\nWhat index do you want to find: ");
    scanf("%d", &findIndex);
    int index = binarySearch(array, findIndex, 0, length - 1);
    printf("The index of %d is: %d\n\n", findIndex, index);


    return 0;
}

//Insertion Sort
void insertionSort(int array[], int length) 
{
    for (int i = 1; i < length; i++) 
    {
        int currentValue = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > currentValue)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = currentValue;
    }
}

//Binary Search
int binarySearch(int array[], int element, int leftIndex, int rightIndex)
{
    int mid = leftIndex + (rightIndex - 1) / 2;

    if (leftIndex > rightIndex)
    {
        return -1;
    }
    
    if (array[mid] == element)
    {
        return mid;
    }
    else if (array[mid] > element)
    {
        return binarySearch(array, element, leftIndex, mid - 1);
    }
    else
    {
        return binarySearch(array, element, mid + 1, rightIndex);
    }
}