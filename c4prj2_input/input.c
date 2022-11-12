#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t * d = malloc(sizeof(*d));
    d -> cards = NULL;
    size_t len_str = strlen(str);
    for (size_t i = 0; i + 1 < len_str; i += 3) {
        if (str[i] != '?'){
            card_t c = card_from_letters(str[i], str[i + 1]);
            add_card_to(d, c);
        }
        else {
            //card_t *c = malloc(sizeof(*c));
            card_t * c = add_empty_card(d);
            add_future_card(fc, str[i + 1] - '0', c);
        }
    }
    return d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    char * line = NULL;
    size_t sz = 0;
    size_t cnt = 0;
    deck_t ** deck_ts = malloc(sizeof(deck_t *)); 
    while ((getline(&line, &sz, f)) >= 0) {
        char * pos1 = strchr(line, ';');
        char * pos2 = strchr(line, '\n');
        *pos1 = '\0';
        *pos2 = '\0';
        size_t len1 = strlen(line);
        size_t len2 = strlen(pos1 + 2);
        if (len1 < 14 || len2 < 14) {
            fprintf(stderr, "Too few cards");
            return NULL; 
        }
        deck_ts = realloc(deck_ts, (cnt + 2) * sizeof(deck_t *));
        deck_ts[cnt] = hand_from_string(line, fc);
        deck_ts[cnt + 1] = hand_from_string(pos1 + 2, fc);
        cnt += 2;
    }
    free(line);
    *n_hands += cnt;
    return deck_ts;
}

