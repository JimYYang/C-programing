#include "cards.h"

int main(void) {

    card_t c1 = card_from_num(30);
    assert_card_valid(c1);
    print_card(c1);

    card_t c2 = card_from_letters('A', 's');
    assert_card_valid(c2);
    print_card(c2);
    
    return 0;
}

