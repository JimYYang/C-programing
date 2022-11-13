#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
    if (index < fc -> n_decks) {
        fc -> decks[index].cards = realloc(fc -> decks[index].cards, (fc -> n_decks + 1) * sizeof(card_t *));
        fc -> decks[index].cards[fc -> decks[index].n_cards] = ptr;
        ++ fc ->decks[index].n_cards;
    }
    else {
        while (fc -> n_decks <= index){
            fc -> decks = realloc(fc -> decks, (fc -> n_decks + 1) * sizeof(*(fc -> decks)));
            fc -> decks[fc -> n_decks].cards = NULL;
            fc -> decks[fc -> n_decks].n_cards = 0;
            ++ fc -> n_decks;
        }
        fc -> decks[index].cards = realloc(fc -> decks[index].cards, (fc -> decks[index].n_cards + 1) * sizeof(card_t *));
        fc -> decks[index].cards[fc -> decks[index].n_cards] = ptr;
        ++ fc ->decks[index].n_cards;
    }
}


void future_cards_from_deck(deck_t * deck, future_cards_t *fc) {
    if (deck -> n_cards < fc -> n_decks) {
        perror("Too few cards in deck");
        return;
    }
    for (size_t i = 0; i < fc -> n_decks; i ++) {
        for (size_t j = 0; j < fc -> decks[i].n_cards; j ++) {
            // can not let this ptr_a = ptr_b !!!
            /* fc -> decks[i].cards[j] = deck -> cards[pos]; */
            fc -> decks[i].cards[j] -> value = deck -> cards[i] -> value;
            fc -> decks[i].cards[j] -> suit = deck -> cards[i] -> suit;
        }
    }
}


