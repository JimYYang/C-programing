#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void rotate(char m[10][10]) {
    int n = 10;
    for (int i = 0; i < n / 2; i ++) {
        for (int j = 0; j < (n + 1) / 2; j ++) {
            char t = m[i][j];
            m[i][j] = m[n - j - 1][i];
            m[n - j - 1][i] = m[n - i - 1][n - j - 1];
            m[n - i - 1][n - j - 1] = m[j][n - i - 1];
            m[j][n - i - 1] = t;
        }
    }
}


int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr,"Usage: encrypt key inputFileName\n");
        return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    char m[10][10];

    int c;
    int row = 0, col = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c != '\n') {
            m[row][col] = c;
            ++ col;
            if (col > 9) {
                ++ row;
                col = 0;
            }
        }
    }

    rotate(m);

    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }

    return 0;
}

