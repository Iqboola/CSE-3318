/*
Simple program used in demo for
- debugger
- system setup

Sample run:
N is 7
 value ->    sum
    10 ->     10
     5 ->     15
     9 ->     24
     0 ->     24
     2 ->     26
     8 ->     34
    20 ->     54

The sum is: 54
Bye
*/

#include <stdio.h>

int main()
{
    int arr[7] = {10, 5, 9, 0, 2, 8, 20 };
    int N = 7;
    int k = 0, mySum = 0, val;

    printf("N is %d\n", N);

    printf("%6s -> %6s\n", "value", "sum");
    k = 0;
    mySum = 0;
    while( k < N  )
    {
        val = arr[k];
        mySum = mySum + val; // mySum += val
        printf("%6d -> %6d\n", val, mySum);
        k++;
    }

    printf("\nThe sum is: %d\n", mySum);
    printf("Bye\n");
    return 0;
}

