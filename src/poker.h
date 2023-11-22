#define HAND_LEN 7
#define MAX_QUAD 1599
#define MAX_STRAIGHT 5863
#define CARD_FIT_ARR_LEN 67

long cards[] = {
    5, 3, 0, 0, 0, 2, 0, 29, 37, 0, 0, 0, 0, 0, 31, 
    0, 7, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    41, 0, 5, 3, 0, 0, 0, 2, 0, 29, 37, 0, 0, 0, 0, 
    0, 31, 0, 7, 23, 2, 3, 5, 7, 11, 13, 17, 19, 0, 
    0, 0, 0, 0, 0, 0, 41, 0
};

typedef struct Card{
    long rank;
    long suit;
} Card;

typedef Card Poket[2];
typedef Card Hand[7];

