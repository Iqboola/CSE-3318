#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void insertionSort(char *words[], int length);
int binarySearch(char* words[], int length, char* word);

int main(int argc, char** argv) 
{
    char *fname_par = NULL;
    char *fname_words = NULL;
    int mode = 0; // 0 - normal, 1 - verbose

    if (argc < 4) 
    {
        printf("Not enough arguments. Need mode and 2 filenames, e.g.:   0 small.txt words1.txt\n");
        return 0;
    }
    else 
    {
        mode = atoi(argv[1]);
        fname_par = argv[2];
        fname_words = argv[3];
    }

    printf("\nmode: %d  |  paragraph: %s  |  words: %s\n", mode, fname_par, fname_words);  // KEEP THIS LINE

    // Open paragraph file
    FILE *fp_par = fopen(fname_par, "r");
    if (fp_par == NULL) 
    {
        printf("Error: Could not open paragraph file. Exiting...\n");
        exit(0);
    }

    // Read paragraph and tokenize words dynamically
    char paragraph[10000];
    char *word = NULL;
    char **words = NULL;
    int wordCount = 0;
    int length = 0;
    int i = 0;

    while (fgets(paragraph, sizeof(paragraph), fp_par)) 
    {
        paragraph[strcspn(paragraph, "\n")] = '\0'; // Remove newline
        length = strlen(paragraph);
        
        // Count words by spaces
        for (int j = 0; j < length; j++) 
        {
            if (paragraph[j] == ' ') 
                wordCount++;
        }
        wordCount++;

        words = malloc(sizeof(char*) * wordCount);
        if (words == NULL) 
        {
            printf("Error: Memory allocation failed. Exiting...\n");
            fclose(fp_par);
            exit(0);
        }

        word = strtok(paragraph, " ");
        while (word != NULL) 
        {
            words[i] = strdup(word);  // Copy each word
            i++;
            word = strtok(NULL, " ");
        }
    }
    fclose(fp_par);

    // Sort the words
    insertionSort(words, wordCount);

    // Print sorted data
    if (mode == 0) 
    {
        printf("\n-- Clean and sorted data --\n");
        for (int i = 0; i < wordCount; i++) 
        {
            printf("%d  %s\n", i, words[i]);
        }
    }
    else if (mode == 1)
    {
        printf("\n-- Clean and sorted data --");
        printf("\n  i  |   pointers[i]    | word\n");
        printf("-----|------------------|------------------\n");

        for (int i = 0; i < wordCount; i++) 
        {
            printf("%4d | %16p | %-10s\n", i, (void *)words[i], words[i]);
        }
    }
    else
    {
        printf("\nInvalid mode selected. Enter either 0 or 1. Exiting...\n");
        exit(0);
    }

    // Perform binary search
    printf("\n-- Binary Search --\n");

    FILE *fp_words = fopen(fname_words, "r");
    if (fp_words == NULL) 
    {
        printf("\nError opening words file\n");
        exit(0);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp_words)) 
    {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline
        for (int i = 0; buffer[i]; i++) 
        {
            buffer[i] = tolower(buffer[i]);  // Convert to lowercase
        }

        printf("%s\n", buffer);

        int check = binarySearch(words, wordCount, buffer);
        if (check >= 0) 
        {
            printf("Found at index %d\n", check);
        }
        else 
        {
            printf("Not found\n");
        }
    }
    fclose(fp_words);

    // Free allocated memory
    for (int i = 0; i < wordCount; i++) 
    {
        free(words[i]);
    }
    free(words);

    return 0;
}

// Insertion sort function
void insertionSort(char *words[], int length) 
{
    for (int i = 1; i < length; i++) 
    {
        char *curr = words[i];
        int j = i - 1;

        while (j >= 0 && strcmp(words[j], curr) > 0) 
        {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = curr;
    }
}

// Binary search function
int binarySearch(char* words[], int length, char* word) 
{
    int left = 0, right = length - 1;
    int iterations = 0;
    printf("%s\n", word);  // Print search term first

    while (left <= right) 
    {
        iterations++;
        int mid = left + (right - left) / 2;
        printf("%d, ", mid);  // Print midpoint

        int cmp = strcmp(word, words[mid]);
        if (cmp == 0) 
        {
            printf("(%d iterations) found\n", iterations);
            return mid;
        } 
        else if (cmp < 0) 
        {
            right = mid - 1;
        } 
        else 
        {
            left = mid + 1;
        }
    }
    printf("(%d iterations) not found\n", iterations);
    return -1;
}
