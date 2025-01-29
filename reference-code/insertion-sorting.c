#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(int a[], int length);

int main () 
{
    int a[] = {8, 4, 9, 5, 7, 6, 3, 2};
    insertionSort(a, 8);

    for (int i = 0; i < 8; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    }
    
    return 0;
}

void insertionSort(int a[], int length)
{
    for (int i = 1; i < length; i++)
    {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}