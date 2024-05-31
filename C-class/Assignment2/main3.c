/**
 *Discussion Forrum 4 Question 2
 */

#include <stdio.h>

int your_function(int array[40][50]) {
    int count = 0;
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 50; j++) {
            int value = array[i][j];
            if (value % 6 == 0 && value % 5 != 0) {
                count++;
            }
        }
    }
    return count;
}

void main() {
    int array[40][50];
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 50; j++) {
            array[i][j] = i * j;
        }
    }
    printf("%d\n", your_function(array));
}
