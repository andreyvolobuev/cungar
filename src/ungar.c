#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "flushes.h"
#include "suited.h"
#include "values.h"
#include "poker.h"

#define RANK_HASH(h) \
        (h[0].rank * \
        h[1].rank * \
        h[2].rank * \
        h[3].rank * \
        h[4].rank * \
        h[5].rank * \
        h[6].rank)

#define SUIT_HASH(h) \
        (h[0].suit * \
         h[1].suit * \
         h[2].suit * \
         h[3].suit * \
         h[4].suit * \
         h[5].suit * \
         h[6].suit)


short evaluate_hand(Hand h) {
    short total;
    long suit_product = SUIT_HASH(h);

    // We first check if there's a flush on board
    short flush_on_board = flushes[suit_product % FLUSHES_LEN];
    if (flush_on_board != 0) {
         // Now it makes sense to check if there's
         // a straight among suited cards
        long suited_cards_product = 1;
        for (int i = 0; i < HAND_LEN; i++) {
            if (h[i].suit == flush_on_board) {
                suited_cards_product *= h[i].rank;
            }
        }
        short straight = values[suited_cards_product % VALUES_LEN];
        if (straight != 0) {
            // We have straight flush so we get just regular staights value
            // and put it on top of the highest quads value. This way our
            // straight flushes will still all be in order but be valued higher
            // then any other combination
            total = straight - MAX_QUAD;
        } else {
            // There's no straight flush on board and it makes no sense
            // to check for quads or full houses as at this point its not
            // possible that these combinations might be on board. So we
            // just return same value as in high card combination put on
            // top of highest straight value
            total = suited[suited_cards_product % SUITED_LEN] - MAX_STRAIGHT;
        }
    } else {
        // At this point we just return precomputed value from a lookup map
        long rank_product = RANK_HASH(h);
        total = values[rank_product % VALUES_LEN];
    }

    return total; 
}


int comp_cards(Card c, Hand h, int limit) {
    for (int i = 0; i < limit; i++) {
        if (c.rank == h[i].rank && c.suit == h[i].suit) {
            return 1;
        }
    }
    return 0;
}


int main(int argc, char* argv[]) {
    if (argc == 2) {
        Hand h;
        int argv_i;
        for (int i = 0; i < 7; i++) {
            char rank = argv[1][argv_i];
            char suit = argv[1][++argv_i];
            h[i].rank = cards[rank % CARD_FIT_ARR_LEN];
            h[i].suit = cards[suit % CARD_FIT_ARR_LEN];
            argv_i++;
        }

        short x = evaluate_hand(h);
        printf("%hi\n", x);

        return 0;
    } else if (argc == 3) {
        Hand h;
        Poket p;
        int argv_i = 0;
        for (int i = 0; i < 2; i++) {
            char rank = argv[1][argv_i];
            char suit = argv[1][++argv_i];
            h[i].rank = cards[rank % CARD_FIT_ARR_LEN];
            h[i].suit = cards[suit % CARD_FIT_ARR_LEN];
            p[i].rank = h[i].rank;
            p[i].suit = h[i].suit;
            argv_i++;
        }

        argv_i = 0;
        for (int i = 2; i < 7; i++) {
            char rank = argv[2][argv_i];
            char suit = argv[2][++argv_i];
            h[i].rank = cards[rank % CARD_FIT_ARR_LEN];
            h[i].suit = cards[suit % CARD_FIT_ARR_LEN];
            argv_i++;
        }
        short min;
        short max;
        short loosers;
        short winners;
        int runs = 0;
        short x = evaluate_hand(h);

        for (int i = 0; i < 13; i++) {
            for (int n = 0; n < 4; n++) {

                Card c1;
                c1.rank = ranks[i];
                c1.suit = suits[n];
                int card_occupied = comp_cards(c1, h, 7);
                if (card_occupied == 1) {
                    continue;
                }
                h[0] = c1;

                for (int j = 0; j < 13; j++) {
                    for (int m = 0; m < 4; m++) {
                        Card c2;
                        c2.rank = ranks[j];
                        c2.suit = suits[m];

                        int card_occupied = comp_cards(c2, h, 7);
                        if (card_occupied == 1) {
                            continue;
                        }
                        h[0] = c2;

                        short result = evaluate_hand(h);
                        if (result < min) {
                            max = result;
                        }
                        if (result > max) {
                            min = result;
                        }
                        if (result < x) {
                            winners++;
                        } else {
                            loosers++;
                        }
                    }
                }
            }
        }

        printf("%hi %hi/%hi %hi/%hi\n", x, loosers, winners, min, max);
        return 0;
    }
    return 1;
}
