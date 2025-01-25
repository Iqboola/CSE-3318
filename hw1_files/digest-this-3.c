#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

void insertionSort(char *words[], int length);

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *words[MAX_WORDS];
    int count = 0;
    char buffer[MAX_WORD_LENGTH];

    // Read words from the file
    while (fscanf(file, "%99s", buffer) == 1) {
        words[count] = malloc(strlen(buffer) + 1);
        if (!words[count]) {
            perror("Memory allocation error");
            return 1;
        }
        strcpy(words[count], buffer);
        count++;
        if (count >= MAX_WORDS) {
            printf("Reached maximum word capacity (%d).\n", MAX_WORDS);
            break;
        }
    }

    fclose(file);

    // Sort the words
    insertionSort(words, count);

    // Print the sorted words
    printf("Sorted words:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }

    return 0;
}

void insertionSort(char *words[], int length)
{
    for (int i = 1; i < length; i++) {
        char *key = words[i];
        int j = i - 1;

        while (j >= 0 && strcmp(words[j], key) > 0) {
            words[j + 1] = words[j];
            j = j - 1;
        }
        words[j + 1] = key;
    }
}
