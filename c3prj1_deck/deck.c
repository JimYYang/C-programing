#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "deck.h"




void print_hand(deck_t * hand){
    size_t n = hand->n_cards;

    for (size_t i = 0; i < n; i ++) {
        print_card(*(hand->cards[i]));
        printf(" ");
    }
    
}

int deck_contains(deck_t * d, card_t c) {
    /* card_t **tmp = d->cards; */
    /* card_t *arr = *tmp; */
    size_t n = d->n_cards;
    for (size_t i = 0; i < n; i ++) {
        if (cmp(*(d->cards[i]), c))
            return 1;
    }
    return 0;
}

void shuffle(deck_t * d){
    size_t n = d->n_cards;

    // srand It's better to call it in the main function once.(That can make value of rand() differ every time).
    // srand is very slow!!!
    // but don't call it in the loop
    // 
    // rand is a sequence. if the seed is same, the sequence is same.
    // random is not used offen.
    /* srand((unsigned)time(0)); */
    for (size_t i = n - 1; i > 0; i --) {
        size_t t = rand() % (i + 1);
        card_t * tmp = d->cards[i];
       	d->cards[i] = d->cards[t];
        d->cards[t] = tmp;
        // card_swap(d->cards[i], d->cards[t]);
    }
}

void assert_full_deck(deck_t * d) {

    for (unsigned i = 0; i < 52; i ++) {
        card_t t = card_from_num(i);
        assert (deck_contains(d, t));
    }    
}

