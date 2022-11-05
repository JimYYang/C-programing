#include <stdlib.h>
#include <stdio.h>

size_t max(size_t a, size_t b);

size_t maxSeq(int * array, size_t n) {
    if (!n)
        return 0;
    size_t res = 1;
    for (size_t i = 0; i < n; i ++) {
        int a = array[i];
        size_t j = i + 1;
        if (j < n) {
            int b = array[j];
            while (a < b) {
                a = b;
                j ++;
                if(j >= n) break;
                b = array[j];
            }
            res = max(res, j - i);
        }
        i = j - 1;
    }
    return res;
}


size_t max(size_t a, size_t b) {
    if (a > b)
        return a;
    return b;
}

