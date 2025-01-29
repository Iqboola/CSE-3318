#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(char *words[], int length);
void printData(int mode, int length, char *originalWords[], char *sortedWords[]);
int binarySearch(char *words[], char *element, int leftIndex, int rightIndex, int *iterations);

int main(int argc, char** argv) 
{
    char *fname_par = NULL;
    char *fname_words = NULL;

    int mode = 0; // 0 - normal, 1 - verbose

    if (argc < 4 ) 
    {
        printf("Not enough arguments. Need mode and 2 filenames, e.g.:   0 small.txt words1.txt\n");
        return 0;
    }
    else 
    {
        fname_par = argv[2];
        fname_words = argv[3];
        mode = atoi(argv[1]);
    }

    printf("\nmode: %d  |  paragraph: %s  |  words: %s\n", mode, fname_par, fname_words);  // KEEP THIS LINE

    //Opens the words text file
    FILE *fp_words = fopen(fname_words, "r");
    if (fp_words == NULL) 
    {
        printf("Error: Could not open file. Exiting...\n");
        exit(0);
    }

    //Dynamically reads words into an array
    const int INITIAL_CAPACITY = 10;
    int capacity = INITIAL_CAPACITY;
    char **words = malloc(capacity * sizeof(*words));
    if (words == NULL) 
    {
        printf("Error: Memory allocation failed. Exiting...\n");
        fclose(fp_words);
        exit(0);
    }

    int length = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp_words)) 
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // Expand array if necessary
        if (length == capacity) 
        {
            capacity *= 2;
            char **temp = realloc(words, capacity * sizeof(*words));
            if (!temp) 
            {
                fprintf(stderr, "Error: Realloc failed.\n");
                for (int i = 0; i < length; i++)
                {
                    free(words[i]);
                }
                free(words);
                fclose(fp_words);
                return 1;
            }
            words = temp;
        }

        // Allocate space for the new word and copy it
        words[length] = malloc(strlen(buffer) + 1);
        if (!words[length]) 
        {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            for (int i = 0; i < length; i++)
            {
                free(words[i]);
            }
            free(words);
            fclose(fp_words);
            return 1;
        }
        strcpy(words[length], buffer);
        length++;
    }
    fclose(fp_words);
    
    //Prints formatted and unformatted data
    if (mode == 0) 
    {
        printf("\n-- Original data --\n");
        for (int i = 0; i < length; i++)
        {
            printf("%d  %s\n", i, words[i]);
        }
        
        insertionSort(words, length);
        
        printf("\n-- Clean and sorted data --\n");    
        for (int i = 0; i < length; i++) 
        {
            printf("%d  %s\n", i, words[i]);
        }

        printf("\n--Binary Search--\n");
        
    }
    else if (mode == 1)
    {
        printf("\n-- Original data --");
        printf("\n  i  |   pointers[i]    | word\n");
        printf("-----|------------------|------------------\n");
    
        for (int i = 0; i < length; i++) 
        {
            printf("%4d | %16p | %-10s\n", i, (void *)words[i], words[i]);
        }
        
        insertionSort(words, length);
        
        printf("\n-- Clean and sorted data --");
        printf("\n  i  |   pointers[i]    | word\n");
        printf("-----|------------------|------------------\n");
    
        for (int i = 0; i < length; i++) 
        {
            printf("%4d | %16p | %-10s\n", i, (void *)words[i], words[i]);
        }
    }
    else
    {
        printf("\nInvalid mode selected. Enter either 0 or 1. Exiting...\n");
        exit(0);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < length; i++) 
    {
        free(words[i]);
    }
    free(words);

    return 0;
}

void insertionSort(char *words[], int length) 
{
    for (int i = 1; i < length; i++) 
    {
        char *wordsPtr = words[i];
        int j = i - 1;

        while (j >= 0 && strcmp(words[j], wordsPtr) > 0) 
        {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = wordsPtr;
    }
}

int binarySearch(char *words[], char *element, int leftIndex, int rightIndex, int *iterations)
{
    if (leftIndex > rightIndex)
    {
        return -1;
    }
    
    (*iterations)++;
    int mid = leftIndex + (rightIndex - 1) / 2;
    int comparison = strcmp(words[mid], element);
    
    if (comparison == 0)
    {
        return mid; // Found
    }
    else if (comparison > 0)
    {
        return binarySearch(words, element, leftIndex, mid - 1, iterations);
    }
    else
    {
        return binarySearch(words, element, mid + 1, rightIndex, iterations);
    }
}