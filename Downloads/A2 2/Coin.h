#ifndef COIN_H
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system.
#define DELIM "," // delimiter

// The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

// enumeration representing the various types of currency available in the system.
enum Denomination
{
    FIVE_CENTS,
    TEN_CENTS,
    TWENTY_CENTS,
    FIFTY_CENTS,
    ONE_DOLLAR,
    TWO_DOLLARS,
    FIVE_DOLLARS,
    TEN_DOLLARS
};

#define Nominal [ 5, 10, 20, 50, 100, 200, 500, 1000 ]
#define NominalLabel [ "5 CENTS" ]

// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    void resetCoinQuantity();



    // the denomination type
    enum Denomination denom;

    // the count of how many of these are in the cash register
    unsigned count;
};

#endif // COIN_H
