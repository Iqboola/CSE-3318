
#include <stdio.h>

void print_array(int A[], int N);

int linear_search(int A[], int N, int val) ;

int binary_search_iter(int A[], int N, int val) ;

int binary_search_rec(int A[], int N, int val) ;
int binary_search_rec_helper(int A[], int left, int right, int val) ;

void run_search(int A[], int N, int val, char search_type);

int main()
{
             //  0  1  2   3   4   5
    int A[10] = {2, 5, 7, 10, 20, 37};
    int N = 6;
    int val = 0;
    char search_type = 'l';


    while (val != -111){

        print_array(A, N);
        printf("\nEnter a value to search for (stop with -111): ");
        scanf("%d", &val);
        printf("Enter the search type linear(l) / binary search iterative (i) / binary search recursive (r): ");
        scanf(" %c", &search_type);
        run_search(A, N, val, search_type);
        printf("\n---------------------------------------");
    }

    return 0;
}

void print_array(int A[], int N){

    printf("\nindexes: ");
    for (int k = 0; k < N ; k++ ){
        printf("%4d,", k);
    }

    printf("\n      A: ");
    for (int k = 0; k < N ; k++ ){
        printf("%4d,", A[k]);
    }
    printf("\n");
}

void run_search(int A[], int N, int val, char search_type) {

    //print_array(A, N);

    printf("Search value: %d\n", val);

    int index;
    if (search_type == 'l'){
        index =  linear_search(A, N, val);
    }
    else if (search_type == 'i'){
        index =  binary_search_iter(A, N, val);
    }
    else if (search_type == 'r'){
        index =  binary_search_rec(A, N, val);
    }
    else {
        printf("Invalid search function type. Return.");
        return ;
    }

    if (index == -1)
        printf("    Not found. Returned: %d\n", -1);
    else
        printf("        Found at index : %d\n", index);
}

/* Linear search
*/
int linear_search(int A[], int N, int val) {

    printf("Linear search\n");

    int i;
    int index = -1;
    for(i = 0; i<N; i++ ){
        if (A[i] == val) {
            index = i;
            break;  // improve. remove break. Discuss operations executed
        }
    }

    return index;
}

/* Iterative binary search
*/
int binary_search_iter(int A[], int N, int val) {

    printf("Binary search iterative\n");

    int left, right, middle; // indexes
    left = 0;
    right = N-1;
    while (left <= right){
        middle = left + (right - left) / 2; // int division in C
        if (A[middle] == val)
            return middle;
        else if (A[middle] < val)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

int binary_search_rec(int A[], int N, int val){
    printf("Binary search recursive\n");
    return binary_search_rec_helper(A, 0, N-1, val);
}

/* Recursive binary search helper
   left  - index of ....
   right - index of ....
*/
int binary_search_rec_helper(int A[], int left, int right, int val){
    if (left > right)
        return -1;

    int middle = left + (right - left)/2;   // avoids overflow
    if (A[middle] == val)
        return middle;
    else if (A[middle] < val )  // val will be in the right hand side, search: [middle+1, right]
        return binary_search_rec_helper(A, middle+1, right, val);
    else                        // val will be in the left hand side, search: [left, middle-1]
        return binary_search_rec_helper(A, left, middle - 1, val);
}
