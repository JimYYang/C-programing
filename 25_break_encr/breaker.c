#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void decrypt(FILE * f, int arr[]) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            c = tolower(c);
            arr[c - 'a'] ++;
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
        perror("Could not open file!");
        return EXIT_FAILURE;
    }
    
    int cnt[26] = {0};
    decrypt(f, cnt);
    char ch = 'a';
    int num = 0;
    for (int i = 0; i < 26; i ++ ) {
        if (cnt[i] > num) {
            num = cnt[i];
            ch = 'a' + i;
        }
    }
    
    int res = (ch - 'e' + 26) % 26;
    printf("%d\n", res);

    return 0;
}

