#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t * d = malloc(sizeof(*d));
    d -> cards = NULL;
    d -> n_cards = 0;
    size_t len_str = strlen(str);
    
    for (size_t i = 0; i < len_str; i ++) {
        if ((str[i] == '\n') || str[i] == ' ') continue;
        if (str[i] == '?') {
            i ++;
            char index[len_str];
            int j = 0;
            while (str[i]!= '\n' && str[i] != ' ') {
                index[j ++] = str[i ++];
            }
            index[j] = '\0';
            add_future_card(fc, atoi(index), add_empty_card(d));
        }
        else {
            add_card_to(d, card_from_letters(str[i], str[i + 1]));
            ++i;
        }
    }
    if (d -> n_cards < 5) {
        fprintf(stderr, "Too few cards");
        return NULL;
    }
    return d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    char * line = NULL;
    size_t sz = 0;
    size_t cnt = 0;
    deck_t ** deck_ts = NULL; 
    while ((getline(&line, &sz, f)) >= 0) {
        deck_ts = realloc(deck_ts, (cnt + 1) * sizeof(deck_t *));
        deck_t * d = hand_from_string(line, fc);
        if (d != NULL) {
            deck_ts[cnt] = d;
            cnt ++;
        }
    }
    free(line);
    *n_hands = cnt;
    return deck_ts;
}

