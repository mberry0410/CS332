#include <stdio.h>

 //Lab 2 
 //to compile: gcc mjbyrd_lab02.c -o lab02
 // to Run: ./lab02

int main() {
    int N;

    //This asks the user for the amount of elements
    printf("Please enter number of elements in array: ");
    scanf("%d", &N);

    int arr[N];

    for (int i = 0; i < N; i++) {
        printf("Please enter element %d of array: ", i + 1);
        scanf("%d", &arr[i]);
    }

    // this displays the original array
    printf("Given array is: [");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[N - 1]);

    // insertion Sort loops
    int temp, currLoc;
    for (int i = 1; i < N; i++) {
        currLoc = i;
        while (currLoc > 0 && arr[currLoc - 1] > arr[currLoc]) {
            temp = arr[currLoc];
            arr[currLoc] = arr[currLoc - 1];
            arr[currLoc - 1] = temp;
            currLoc--;
        }
    }

    // Displays the array after sorting
    printf("Sorted array is: [");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[N - 1]);

    return 0;
}