#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("mode: %d  |  paragraph: %s  |  words: %s\n", mode, fname_par, fname_words);  // KEEP THIS LINE

    return 0;
}