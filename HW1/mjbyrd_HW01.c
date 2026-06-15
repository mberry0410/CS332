#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//five functions:
int sumOfDigits(int n) {
    if (n <= 0) {
        return -1;
    }

    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int UABMaxMinDiff(int arr[], int size) {
    int max = arr[0];
    int min = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    return max - min;
}

void replaceEvenWithZero(int arr[], int size, int result[]) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            result[i] = 0;
        } else {
            result[i] = arr[i];
        }
    }
}

bool perfectSquare(int n) {
    if (n < 0) {
        return false;
    }

    int root = (int)sqrt(n);
    return (root * root == n);
}

int countVowels(char s[]) {
    int count = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = tolower(s[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' ||
            ch == 'o' || ch == 'u') {
            count++;
        }
    }

    return count;
}

void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // These test the sumOfDigits function
    printf("sumOfDigits(123) = %d\n", sumOfDigits(123));
    printf("sumOfDigits(405) = %d\n", sumOfDigits(405));
    printf("sumOfDigits(0) = %d\n", sumOfDigits(0));
    printf("sumOfDigits(7) = %d\n", sumOfDigits(7));
    printf("sumOfDigits(-308) = %d\n\n", sumOfDigits(-308));

    // Tests UABMaxMinDiff function
    int arr1[] = {3, 7, 2, 9};
    int arr2[] = {5, 5, 5, 5, 5, 5};
    int arr3[] = {-2, 4, -1, 6, 5};

    printf("UABMaxMinDiff(arr1) = %d\n",
           UABMaxMinDiff(arr1, 4));
    printf("UABMaxMinDiff(arr2) = %d\n",
           UABMaxMinDiff(arr2, 6));
    printf("UABMaxMinDiff(arr3) = %d\n\n",
           UABMaxMinDiff(arr3, 5));

    // Tests  replaceEvenWithZero function
    int evenArr1[] = {1, 2, 3, 4};
    int evenArr2[] = {2, 4, 6};
    int evenArr3[] = {1, 3, 5};

    int result1[4];
    int result2[3];
    int result3[3];

    replaceEvenWithZero(evenArr1, 4, result1);
    replaceEvenWithZero(evenArr2, 3, result2);
    replaceEvenWithZero(evenArr3, 3, result3);

    printf("replaceEvenWithZero([1,2,3,4]) = ");
    printArray(result1, 4);

    printf("replaceEvenWithZero([2,4,6]) = ");
    printArray(result2, 3);

    printf("replaceEvenWithZero([1,3,5]) = ");
    printArray(result3, 3);

    printf("\n");

    // Tests perfectSquare fucntion
    printf("perfectSquare(16) = %s\n",
           perfectSquare(16) ? "True" : "False");
    printf("perfectSquare(15) = %s\n",
           perfectSquare(15) ? "True" : "False");
    printf("perfectSquare(25) = %s\n",
           perfectSquare(25) ? "True" : "False");
    printf("perfectSquare(36) = %s\n\n",
           perfectSquare(36) ? "True" : "False");

    // Tests countVowels function
    printf("countVowels(\"Hello World\") = %d\n",
           countVowels("Hello World"));
    printf("countVowels(\"UAB CS\") = %d\n",
           countVowels("UAB CS"));
    printf("countVowels(\"Python\") = %d\n",
           countVowels("Python"));
    printf("countVowels(\"aeiou\") = %d\n",
           countVowels("aeiou"));

    return 0;
}