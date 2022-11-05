#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"

int cmp(card_t a, card_t b) {
    if (a.suit == b.suit && a.value == b.value)
        return 1;
    return 0;  
}

void card_swap(card_t *a, card_t *b) {
    unsigned t1 = a->value;
    suit_t t2 = a->suit;

    a->value = b->value;
    a->suit = b->suit;
    b->value = t1;
    b->suit = t2;
}

void assert_card_valid(card_t c) {
    assert(c.value >= 2 && c.value <= VALUE_ACE && c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
    switch (r) {
        case STRAIGHT_FLUSH:
            return "STRAIGHT_FLUSH";
        case FOUR_OF_A_KIND:
            return "FOUR_OF_A_KIND";
        case FULL_HOUSE:
            return "FULL_HOUSE";
        case FLUSH:
            return "FLUSH";
        case STRAIGHT:
            return "STRAIGHT";
        case THREE_OF_A_KIND:
            return "THREE_OF_A_KIND";
        case TWO_PAIR:
            return "TWO_PAIR";
        case PAIR:
            return "PAIR";
        default:
            return "NOTHING";
    }
  return "";
}

char value_letter(card_t c) {
  if (c.value >= 2 && c.value <= 9)
      return '0' + c.value;
  if (c.value == 10)
      return '0';
  if (c.value == 11)
      return 'J';
  if (c.value == 12)
      return 'Q';
  if (c.value == 13)
      return 'K';

  return 'A';
}


char suit_letter(card_t c) {
  if (c.suit == SPADES)
      return 's';
  if (c.suit == HEARTS)
      return 'h';
  if (c.suit == DIAMONDS)
      return 'd';

  return 'c';
  
}

void print_card(card_t c) {
  char val = value_letter(c);
  char suit = suit_letter(c);
  printf("%c%c", val, suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if (value_let >= '2' && value_let <= '9')
      temp.value = value_let - '0';
  else if (value_let == '0')
      temp.value = 10;
  else {
      switch(value_let){
          case 'J':
              temp.value = 11;
              break;
          case 'Q':
              temp.value = 12;
              break;
          case 'K':
              temp.value = 13;
              break;
          case 'A':
              temp.value = 14;
              break;
          default:
              printf("The value_let \"%c\" is illegal!", value_let);
              exit(EXIT_FAILURE); 
      }
  }
  
  switch(suit_let){
      case 's':
          temp.suit = SPADES;
          break;
      case 'h':
          temp.suit = HEARTS;
          break;
      case 'd':
          temp.suit = DIAMONDS;
          break;
      case 'c':
          temp.suit = CLUBS;
          break;
      default:
          printf("The suit_let \"%c\" is illegal!", suit_let);  
          exit(EXIT_FAILURE);
  }

  return temp;
}

card_t card_from_num(unsigned c) {
  suit_t suit_c = c / 13;
  unsigned value_c = c % 13 + 2;
  card_t temp;
  temp.suit = suit_c;
  temp.value = value_c;
  return temp;
}

