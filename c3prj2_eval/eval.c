#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>


unsigned max_unsign(unsigned a, unsigned b) {
    if (a > b) return a;
    return b;
}

int card_ptr_comp(const void * vp1, const void * vp2) {
    const card_t *const* cp1 = vp1;
    const card_t *const* cp2 = vp2;
    if ((**cp1).value > (**cp2).value)
        return -1;
    else if ((**cp1).value < (**cp2).value)
        return 1;
    else if ((**cp1).suit > (**cp2).suit)
        return -1;
    else if ((**cp1).suit < (**cp2).suit)
        return 1;

    return 0;
}

suit_t flush_suit(deck_t * hand) {
    card_t ** card = hand -> cards;

    int s = 0, h = 0, d = 0, c = 0;

    for (size_t i = 0; i < hand -> n_cards; i ++) {
        card_t cur = **(card + i);

        switch (cur.suit) {
            case SPADES:
                s ++;
                break;
            case HEARTS:
                h ++;
                break;
            case DIAMONDS:
                d ++;
                break;
            case CLUBS:
                c ++;
                break;
            default:
                break;
        }
    }

    if (s >= 5) return SPADES;
    if (h >= 5) return HEARTS;
    if (d >= 5) return DIAMONDS;
    if (c >= 5) return CLUBS;
    
    return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
    unsigned res = arr[0];

    for (size_t i = 1; i < n; i ++) {
        if (res < arr[i])
            res = arr[i];
    }
    return res;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){

    for (size_t i = 0; i < n; i ++) {
        if (match_counts[i] == n_of_akind) {
            return i;
        }
    }

    /* assert(idx != -1); */
    return 0;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
    card_t ** card = hand -> cards;
    card_t matched = *(card[match_idx]); 

    for (size_t i = 0; i < hand -> n_cards; i ++) {
        if ((match_counts[i] > 1) && (card[i] -> value != matched.value)) {
            return i;
        }
    }
    return -1;
}


/* ssize_t get_index_5(deck_t * hand) { */
/*     ssize_t res = -1; */
/*     for (size_t i = 0; i < hand ->n_cards; i ++) { */
/*         if (hand -> cards[i] -> value == 5){ */
/*             res = i; */
/*             break; */
/*         } */
/*     } */
/*     return res; */
/* } */

/* int get_straight_len(deck_t *hand, size_t index) { */
/*     int cnt = 1; */
/*     card_t ** card = hand -> cards; */
/*     unsigned v = (*card[index]).value; */
/*     unsigned next_v = v; */
/*     size_t len = hand -> n_cards; */
/*     for (size_t i = index; i < len; i ++) { */
/*         size_t j = i + 1; */
/*         while (j < len && card[j] -> value == v) j ++; */
/*         if (j < len) */
/*             next_v = card[j] -> value; */
/*         if (next_v == v - 1) */
/*             ++ cnt; */
/*         else */
/*             break; */
/*         v = next_v; */
/*         i = j - 1; */
/*     } */

/*     return cnt; */
/* } */


/* ssize_t get_index_5_suit(deck_t * hand, size_t index, suit_t fs) { */
/*     card_t ** card = hand -> cards; */
/*     unsigned v = card[index] -> value; */ 
/*     size_t len = hand -> n_cards; */
/*     ssize_t idx = -1; */

/*     // first, find if there is a card, whose value = 5, suit = fs, if not return 0; */
/*     // if has, this must be contained(if has multiple cards qualified, selecting the min-index is ok). */
/*     for (size_t i = index; i < len; i ++) { */
/*         size_t j = i + 1; */
/*         while (j < len && card[j] -> value == v && card[j] -> suit != fs) j ++; */
/*         if (j < len) { */
/*             if (card[j] -> value == v && card[j] -> suit == fs){ */
/*                 idx = j; */
/*                 break; */
/*             } */
/*             else */
/*                 return -1; */
/*         } */
/*     } */

/*     return idx; */

/* } */


/* // this function don't need to contain the card in index!!! */
/* int get_straight_flush_len(deck_t * hand, size_t index, suit_t fs) { */
/*     int cnt = 1; */
/*     card_t ** card = hand -> cards; */
/*     unsigned v = (*card[index]).value; */
/*     suit_t s = (*card[index]).suit; */
/*     unsigned next_v = v; */
/*     size_t len = hand -> n_cards; */

/*     // first, find if there is a card, whose value = 5, suit = fs, if not return 0; */
/*     // if has, this must be contained(if has multiple cards qualified, selecting the min-index is ok). */
/*     // and if n == 5, the index will not changed. */
/*     // because the value and the suit of the card in index both have been checked. */
    
/*     ssize_t idx = get_index_5_suit(hand, index, fs); */
/*     if (idx == -1) */
/*         return 0; */

/*     for (size_t i = idx; i < len; i ++) { */
/*         size_t j = i + 1; */
/*         while (j < len && card[j] -> value == v) j ++; */
/*         if (j < len) */ 
/*             next_v = card[j] -> value; */
        
/*         while (j < len && card[j]->value == next_v && card[j] -> suit != fs) ++ j; */

/*         if (j < len) { */
/*             next_v = card[j] -> value; */
/*             s = card[j] ->suit; */
/*         } */
/*         if (next_v == v - 1 && s == fs) */
/*             ++ cnt; */
/*         else */
/*             break; */
/*         v = next_v; */
/*         i = j - 1; */
/*     } */

/*     return cnt; */
/* } */

/* int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) { */
/*     // cnt1 is the length of straight */

/*     int cnt1 = get_straight_len(hand, index); */

/*     if (cnt1 == n) { */
/*         if (fs == NUM_SUITS) */
/*             return 1; */

/*         suit_t type = flush_suit(hand); */
/*         if (type == fs) { */
/*             suit_t s = hand -> cards[index] -> suit; */
/*             // nota that according to the principle of short circuit, n == 5 must precede b. */
/*             if (n == 5 && s != fs) // when n = 5, the card in index is must be contained. */
/*                 // while when n = 4, the first card 5 may be not contained. */
/*                 return 0; // write like this(the line and the above) suppose that the straight flush contain the index!!! */

/*             int cnt2 = get_straight_flush_len(hand, index, fs); */
/*             if (cnt2 == n) */
/*                 return 1; */
/*             else */
/*                 return 0; */
/*         } */
/*         else return 0; */
/*     } */

/*     return 0; */
/* } */


/* int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) { */
/*     return is_n_length_straight_at(hand, index, fs, 4); */
/* } */

/* int is_straight_at(deck_t * hand, size_t index, suit_t fs) { */
/*     card_t **card = hand -> cards; */
/*     unsigned val = card[index] -> value; */
/*     if (val != VALUE_ACE) */
/*         return is_n_length_straight_at(hand, index, fs, 5); */
    
/*     int ace_high = is_n_length_straight_at(hand, index, fs, 5); */
/*     if (ace_high) */
/*         return ace_high; */    

/*     ssize_t idx_5 = get_index_5(hand); */
/*     suit_t s = card[index] -> suit; */
/*     int ace_low = 0; */
/*     if (idx_5 != -1 && s == fs) */
/*         ace_low = is_n_length_straight_at(hand, idx_5, fs, 4); */

/*     return ace_low; */
/* } */


int straight_helper(deck_t * hand, size_t index, suit_t fs, int suit, int count, size_t n)
{
  unsigned value = hand->cards[index]->value;
  for(;index < n; ++index)
    {
      if(hand->cards[index]->suit == fs && (hand->cards[index]->value == value || hand->cards[index]->value == (value + 1)))
	{
	  ++suit;
	}
      if(hand->cards[index]->value == value)
	{
	  ++count;
	  --value;
	}
      if(count == 5 && (fs == NUM_SUITS || suit == 5)) return 1;
    }
  return 0;
}


int is_straight_at(deck_t * hand, size_t index, suit_t fs)
{
  int count = 0;
  int suit = 0;
  size_t origIndex = index;
  size_t n = hand->n_cards;
  if(n-index < 5) return 0;

  if(fs != NUM_SUITS && hand->cards[index]->suit != fs ) return 0;
  if(hand->cards[index]->value == VALUE_ACE && hand->cards[n-1]->value == 2)
    {
      ++count;
      for(int i = 0; i < 4; ++i)
	{
	  if(hand->cards[i]->value == VALUE_ACE && hand->cards[i]->suit == fs)
	    {
	      ++suit;
	    }
	}
      while(index < hand->n_cards)
	{
	  if(hand->cards[index]->value == 5)
	    {
	      break;
	    }
	  ++index;
	}
      if(index != hand->n_cards)
	{
	  if(straight_helper(hand, index, fs, suit, count, n) == 1) return -1;
	}
    }
  index = origIndex;
  suit =0;
  count = 0;
  if(straight_helper(hand, index, fs, suit, count, n) == 1)
    {
      return 1;
    }
  return 0;
}



hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
    hand_eval_t ans;
    ans.ranking = what;
    card_t ** card = hand -> cards;
    size_t cnt = 0;
    for (size_t i = idx; i < idx + n; i ++) {
        ans.cards[cnt ++] = card[i];
    }

    if (cnt < 5) {
        for (size_t i = 0; i < hand -> n_cards; i ++) {
            if (i >= idx && i < idx + n)
                continue;
            ans.cards[cnt ++] = card[i];
            if (cnt == 5)
                break;
        }
    }
    return ans;
}

void sortCard(card_t ** card, size_t n) {
    qsort(card, n, sizeof (card_t), card_ptr_comp);
}

int compare_hands(deck_t * hand1, deck_t * hand2) {
    /* sortCard(hand1 -> cards, hand1 -> n_cards); */
    /* sortCard(hand2 -> cards, hand2 -> n_cards); */
    qsort(hand1->cards, hand1->n_cards, sizeof(card_t), card_ptr_comp);
    qsort(hand2->cards, hand2->n_cards, sizeof(card_t), card_ptr_comp);

    hand_eval_t h1 = evaluate_hand(hand1);
    hand_eval_t h2 = evaluate_hand(hand2);

    if (h1.ranking < h2.ranking)
        return 1;
    if (h1.ranking > h2.ranking)
        return -1;
    for (size_t i = 0; i < 5; i ++) {
        card_t *c1 = h1.cards[i];
        card_t *c2 = h2.cards[i];

        if (c1 -> value > c2 -> value)
            return 1;
        if (c1 -> value < c2 -> value)
            return -1;
    }

    return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) {
    unsigned * arr = malloc((hand -> n_cards) * sizeof(*arr));
    for (size_t i = 0; i < hand -> n_cards; i ++) {
        size_t j = i + 1;
        while (j < hand -> n_cards && hand -> cards[i] -> value == hand -> cards[j] -> value) {
            j ++;
        }
        unsigned len = j - i;
        for (size_t k = i; k < j; k ++){
            arr[k] = len;
        }
        i = j - 1;
    }

    return arr;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}


