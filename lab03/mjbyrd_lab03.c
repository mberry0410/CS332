#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Madison Byrd (mjbyrd)
// lab03
// Compile: gcc mjbyrd_lab03.c -o mjbyrd_lab03
//Run: ./mjbyrd_lab03


void readStrings(char **arr, int size);
void sortStrings(char **arr, int size);
void displayStrings(char **arr, int size);

int main(int argc, char **argv)
{
    int N, i;

    printf("Please enter number of strings: ");
    scanf("%d", &N);

    // Allocates memory for array of string pointers
    char **arr = (char **) malloc(N * sizeof(char *));

    // reads the strings from user
    readStrings(arr, N);

    printf("Given array is: ");
    displayStrings(arr, N);

    sortStrings(arr, N);
    
    //this displays the sorted array 
    printf("Sorted array is: ");
    displayStrings(arr, N);

    // Free memory
    for (i = 0; i < N; i++)
    {
        free(arr[i]);
    }

    free(arr);

    return 0;
}

void readStrings(char **arr, int size)
{
    int i;
    char temp[100];

    for (i = 0; i < size; i++)
    {
        printf("Please enter string %d of array: ", i + 1);
        scanf("%99s", temp);

        //tis allocates memory for each string based on its length 
        arr[i] = (char *) malloc((strlen(temp) + 1) * sizeof(char));

        strcpy(arr[i], temp);
    }
}

void sortStrings(char **arr, int size)
{
    int i, currLoc;
    char *temp;

    for (i = 1; i < size; i++)
    {
        currLoc = i;

        //does insertion sort on the strings
        while (currLoc > 0 && strcmp(arr[currLoc - 1], arr[currLoc]) > 0)
        {
            temp = arr[currLoc];
            arr[currLoc] = arr[currLoc - 1];
            arr[currLoc - 1] = temp;

            currLoc--;
        }
    }
}

void displayStrings(char **arr, int size)
{
    int i;

    printf("[");

    for (i = 0; i < size - 1; i++)
    {
        printf("%s, ", arr[i]);
    }

    printf("%s]\n", arr[size - 1]);
}
