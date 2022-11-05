#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void rotate(char matrix[10][10]) {
    char tmp[10][10];

    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            tmp[j][9 - i] = matrix[i][j];
        }
    }
    memcpy(matrix, tmp, 100);
}

