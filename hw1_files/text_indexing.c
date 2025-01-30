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
    int mode = 0;

    if (argc < 4) 
    {
        printf("Usage: ./program mode paragraph.txt words.txt\n");
        return 0;
    } 
    else 
    {
        mode = atoi(argv[1]);
        fname_par = argv[2];
        fname_words = argv[3];
    }

    printf("mode: %d  |  paragraph: %s  |  words: %s\n", mode, fname_par, fname_words);

    FILE *fp_par = fopen(fname_par, "r");
    if (!fp_par) 
    {
        printf("Error: Could not open paragraph file.\n");
        exit(1);
    }

    char paragraph[1024];
    fgets(paragraph, sizeof(paragraph), fp_par);
    fclose(fp_par);

    int paraCapacity = 10;
    int paraLength = 0;
    char **paraWords = malloc(paraCapacity * sizeof(char*));

    char *token = strtok(paragraph, " ");
    while (token != NULL) 
    {
        char cleaned[256];
        int i = 0, j = 0;
        while (token[i]) 
        {
            if (isalpha(token[i])) 
            {
                cleaned[j++] = tolower(token[i]);
            }
            i++;
        }
        cleaned[j] = '\0';

        if (paraLength == paraCapacity) 
        {
            paraCapacity *= 2;
            paraWords = realloc(paraWords, paraCapacity * sizeof(char*));
        }
        paraWords[paraLength] = strdup(cleaned); // Copy cleaned word
        paraLength++;

        token = strtok(NULL, " ");
    }

    insertionSort(paraWords, paraLength);

    if (mode == 0) 
    {
        printf("\n-- Original data --\n");
        for (int i = 0; i < paraLength; i++) 
        {
            printf("%d  %s\n", i, paraWords[i]);
        }
        printf("\n-- Clean and sorted data --\n");
        for (int i = 0; i < paraLength; i++) 
        {
            printf("%d  %s\n", i, paraWords[i]);
        }
    } 
    else if (mode == 1) 
    {
        printf("\n-- Original data --\n  i  |   pointers[i]    | word\n-----|------------------|------------------\n");
        for (int i = 0; i < paraLength; i++) 
        {
            printf("%4d | %16p | %s\n", i, (void*)paraWords[i], paraWords[i]);
        }
        printf("\n-- Clean and sorted data --\n  i  |   pointers[i]    | word\n-----|------------------|------------------\n");
        for (int i = 0; i < paraLength; i++) 
        {
            printf("%4d | %16p | %s\n", i, (void*)paraWords[i], paraWords[i]);
        }
    }

    printf("\n-- Binary search --\n");
    FILE *fp_words = fopen(fname_words, "r");
    if (!fp_words) 
    {
        printf("Error: Could not open words file.\n");
        exit(1);
    }

    char searchWord[256];
    while (fgets(searchWord, sizeof(searchWord), fp_words)) 
    {
        searchWord[strcspn(searchWord, "\n")] = '\0'; 
        char cleaned[256];
        int i = 0, j = 0;
        while (searchWord[i]) {
            if (isalpha(searchWord[i])) 
            {
                cleaned[j++] = tolower(searchWord[i]);
            }
            i++;
        }
        cleaned[j] = '\0';

        printf("%s\n", cleaned);
        int result = binarySearch(paraWords, paraLength, cleaned);
        if (result == -1) 
        {
            printf("not found\n");
        } else 
        {
            printf("found\n");
        }
    }
    fclose(fp_words);

    for (int i = 0; i < paraLength; i++) free(paraWords[i]);
    free(paraWords);

    return 0;
}

int binarySearch(char* words[], int length, char* word) 
{
    int left = 0, right = length - 1;
    int iterations = 0;

    while (left <= right) 
    {
        iterations++;
        int mid = left + (right - left) / 2;
        printf("%d, ", mid);

        int cmp = strcmp(word, words[mid]);
        if (cmp == 0) 
        {
            printf("(%d iterations) ", iterations);
            return mid;
        } else if (cmp < 0) 
        {
            right = mid - 1;
        } else 
        {
            left = mid + 1;
        }
    }
    printf("(%d iterations) ", iterations);
    return -1;
}


void insertionSort(char *words[], int length) 
{
    for (int i = 1; i < length; i++) 
    {
        char *current = words[i];
        int j = i - 1;
        while (j >= 0 && strcmp(words[j], current) > 0) 
        {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = current;
    }
}