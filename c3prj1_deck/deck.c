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




void add_card_to(deck_t * deck, card_t c) {
    // must allocate memory first
    card_t * t = malloc(sizeof(*t));
    t -> value = c.value;
    t -> suit = c.suit;
    deck -> cards = realloc(deck -> cards, ((deck -> n_cards) + 1) * sizeof(card_t *)); 
    deck -> cards[deck -> n_cards] = t;
    // writing as following is not true
    // because we only have memory for card_t *, but not card_t
    /* deck -> cards[deck -> n_cards] -> value = c.value; */
    /* deck -> cards[deck -> n_cards] -> suit = c.suit; */
    ++ deck -> n_cards;
}


card_t * add_empty_card(deck_t * deck) {
    card_t * card = malloc(sizeof(card_t));
    card -> value = 0;
    card -> suit = 0;
    add_card_to(deck, *card);
    return deck -> cards[deck -> n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
    deck_t * d = malloc(sizeof (*d));
    d -> cards = NULL;
    d -> n_cards = 0;
    //d -> cards = malloc(excluded_cards -> n_cards * sizeof(card_t *));
    for (unsigned i = 0; i < 52; i ++) {
        card_t c = card_from_num(i);
        if (!deck_contains(excluded_cards, c))
            add_card_to(d, c);
    }        
    return d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
    deck_t * excluded_cards = malloc(sizeof(*excluded_cards));

    excluded_cards -> cards = NULL;
    excluded_cards -> n_cards = 0;

    for (size_t i = 0; i < n_hands; i ++) {
        for (size_t j = 0; j < hands[i] -> n_cards; j ++) {
            if (!deck_contains(excluded_cards, *(hands[i] -> cards[j])))
                add_card_to(excluded_cards, *(hands[i] -> cards[j]));
        }
    }
    return make_deck_exclude(excluded_cards);
}

void free_deck(deck_t * deck) {
    for(size_t i = 0; i < deck -> n_cards; i ++) {
        free(deck -> cards[i]);
    }
    free(deck -> cards);
    free(deck);
}


