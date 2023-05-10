#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include "Coin.h"
using namespace std;

// The length of the id string not counting the nul terminator
#define IDLEN 5

// The maximum length of a product name not counting the nul terminator
#define NAMELEN 40

// The maximum length of a product description not counting the nul terminator.
#define DESCLEN 255

// The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

// The default stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_STOCK_LEVEL 20

// The number of denominations of currency available in the system
#define NUM_DENOMS 8

/**
 * a structure to represent a price. One of the problems with the floating
 * point formats in C++ like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
class Price
{
public:
    Price();
    Price(string price_str);
    Price(int price);

    string getPrice();
    Price substractPrice(Price p);
    bool isPaid();

    vector<string> denomList();

    // The dollar value, and the cents value for some price
    unsigned dollars, cents;
};

/**
 * data structure to represent a stock item within the system
 **/
class Stock
{
public:
    Stock();
    string getAvailable();
    void resetStock();

    // the unique id for this item
    string id;

    // the name of this item
    string name;

    // the description of this item
    string description;

    // the price of this item
    Price price;

    // how many of this item do we have on hand?
    unsigned on_hand;
};

/**
 * the node that holds the data about an item stored in memory
 **/
class Node
{
public:
    Node();
    Node(Stock *data);
    ~Node();
    // pointer to the data held for the node
    Stock *data;
    // pointer to the next node in the list
    Node *next;
};

#endif // NODE_H