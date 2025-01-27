#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(char *words[], int length) 
{
    for (int i = 1; i < length; i++) 
    {
        // wordsPtr is the pointer to the current string
        char *wordsPtr = words[i];
        int j = i - 1;

        // Use strcmp to compare strings instead of comparing the first character
        while (j >= 0 && strcmp(words[j], wordsPtr) > 0) 
        {
            words[j + 1] = words[j];
            j--;
        }

        // Insert wordsPtr into correct position
        words[j + 1] = wordsPtr;
    }
}

int main() {
    char *words[] = {"apple", "banana", "cherry"};
    int length = 3;

    insertionSort(words, length);

    printf("-- Clean and sorted data --");
    printf("\n  i  |   pointers[i]    | word\n");
    printf("-----|------------------|------------------\n");
    
    for (int i = 0; i < length; i++) 
    {
        // Cast the char* to void* when printing with %p
        printf("%4d | %15p | %s\n", i, (void*)words[i], words[i]);
    }

    return 0;
}