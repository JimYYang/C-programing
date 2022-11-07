#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>



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


int CheckInputFormat(char * a) {
    char * suffix = ".txt";
    size_t s1 = strlen(a);
    size_t s2 = strlen(suffix);
    return s1 >= s2 && (strcmp(a + s1 -s2, suffix) == 0);
}


int CheckFileContents(FILE * f) {
    int c;
    int rows = 0;
    int total_chars = 0;

    c = fgetc(f);

    while (c != EOF) {
        if (c == 0xFF) continue;
        if (c != '\n' && isprint(c)) ++ total_chars;
        if (c == '\n') ++ rows;
        c = fgetc(f);
    }
    if (rows == 10 && total_chars == 100)
        return 1;
    return 0;
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

    char * filename = argv[1];

    if (!CheckInputFormat(filename)) {
        perror("Invalid file format!");
        return EXIT_FAILURE;
    }

    if (!CheckFileContents(f)) {
        perror("Invalid file contents!");
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
    
    if (fclose(f) != 0) {
        perror("File did not close successfully!");
        return EXIT_FAILURE;
    }

    return 0;
}

