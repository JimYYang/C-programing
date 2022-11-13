#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


size_t win_hand(deck_t ** deck_ts, size_t n_hands) {

    int cnt[n_hands + 1];
    memset(cnt, 0, sizeof cnt);
    for (size_t j = 0; j < n_hands; j ++) {
        for (size_t k = j + 1; k < n_hands; k ++) {
          int res = compare_hands(deck_ts[j], deck_ts[k]);
          if (res == 1)
              cnt[j] ++;
          else if(res == -1)
              cnt[k] ++;
          else 
              cnt[n_hands]++;
        }
    }
    size_t largest = 0;
    for (size_t i = 1; i <= n_hands; i ++) {
        if (cnt[i] > cnt[largest]) largest = i;
    }

    int num = 0;

    for (size_t i = 0; i <= n_hands; i ++) {
       if (cnt[i] == cnt[largest]) ++ num;
       if (num > 1) return n_hands;
    }
    return largest;
}

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
    
    if (argc < 2) {
        perror("Too few arguments");
        return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r");
    int trail_times = 0;
    if (argc == 2) {
        trail_times = 10000;
    }
    else {
        trail_times = atoi(argv[2]);
    }

    size_t n_hands = 0;
    future_cards_t * fc = malloc(sizeof(*fc));
    fc -> decks = NULL;
    fc -> n_decks = 0;
    deck_t ** deck_ts = read_input(f, &n_hands, fc);
    deck_t * remain = build_remaining_deck(deck_ts, n_hands);
    int cnt[n_hands + 1];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < trail_times; i ++) {
        shuffle(remain);
        future_cards_from_deck(remain, fc);
        size_t idx = win_hand(deck_ts, n_hands);
        cnt[idx] ++;
    }

    for (size_t i = 0; i < n_hands; i ++) {
        printf("Hand %zu won %u / %u times (%.2f%%)\n", i, cnt[i], trail_times, (float)cnt[i] / trail_times * 100);
    }
    printf("And there were %u ties\n", cnt[n_hands]);

    for (size_t i = 0; i < fc -> n_decks; i ++) {
        if (fc -> decks[i].n_cards) free(fc -> decks[i].cards);
    }
    free(fc -> decks);
    free(fc);
    
    for (size_t i = 0; i < n_hands; i ++) {
        free_deck(deck_ts[i]);
    }
    free(deck_ts);
    free_deck(remain);

    if (fclose(f) != 0) {
        perror("Can not close file");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

