#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(char *words[], int length) 
{
    for (int i = 1; i < length; i++) 
    {
        char *key = words[i];
        int j = i - 1;

        while (j >= 0 && strcmp(words[j], key) > 0) 
        {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = key;
    }
}

int main(int argc, char *argv[])
{
    // 1. Check command-line arguments
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // 2. Open the file passed as argument
    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return 1; 
    }

    // 3. Read lines into a dynamically‐allocated array of char*
    //    We start with some initial capacity and expand as needed.
    const int INITIAL_CAPACITY = 10;
    int capacity = INITIAL_CAPACITY;
    char **words = malloc(capacity * sizeof(*words));
    if (!words)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(fp);
        return 1;
    }

    int length = 0;
    char buffer[256];  // Buffer for reading each line

    while (fgets(buffer, sizeof(buffer), fp))
    {
        // Remove trailing newline, if any
        buffer[strcspn(buffer, "\n")] = '\0';

        // Expand array if necessary
        if (length == capacity)
        {
            capacity *= 2;
            char **temp = realloc(words, capacity * sizeof(*words));
            if (!temp)
            {
                fprintf(stderr, "Error: Realloc failed.\n");
                // Clean up
                for (int i = 0; i < length; i++)
                    free(words[i]);
                free(words);
                fclose(fp);
                return 1;
            }
            words = temp;
        }

        // Allocate space for the new word and copy it
        words[length] = malloc(strlen(buffer) + 1);
        if (!words[length])
        {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            // Clean up
            for (int i = 0; i < length; i++)
                free(words[i]);
            free(words);
            fclose(fp);
            return 1;
        }
        strcpy(words[length], buffer);
        length++;
    }
    fclose(fp);

    // 4. Sort the array
    insertionSort(words, length);

    // 5. Print in a formatted table
    printf("\n");
    printf("  i  |pointers[i]|  word\n");
    printf("-----|-----------|--------------\n");
    
    for (int i = 0; i < length; i++) 
    {
        // %4d => right‐align integer in at least 4 spaces
        // %20p => right‐align pointer in at least 20 spaces
        // %-10s => left‐align string in a 10‐character field
        printf("%4d |%11p| %-10s\n", i, (void *)words[i], words[i]);
    }

    // 6. Free dynamically allocated memory
    for (int i = 0; i < length; i++)
    {
        free(words[i]);
    }
    free(words);

    return 0;
}
