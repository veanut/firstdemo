#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Node::Node()
{
    this->data = NULL;
    this->next = NULL;
};

Node::Node(Stock *data)
{
    this->data = data;
    this->next = NULL;
};

Node::~Node()
{
    cout << "Node destructed" << endl;
};

Stock::Stock()
{
    this->on_hand = DEFAULT_STOCK_LEVEL;
}

string Stock::getAvailable()
{
    int av = this->on_hand;
    return to_string(av);
}

void Stock::resetStock()
{
    this->on_hand = DEFAULT_STOCK_LEVEL;
}

Price::Price()
{
}

Price::Price(string price_str)
{
    int dot = price_str.find('.');
    string d = price_str.substr(0, dot);
    string c = price_str.substr(dot + 1, price_str.length() - d.length() - 1);

    this->dollars = stoi(d);
    this->cents = stoi(c);
}

Price::Price(int price)
{
    int d = price / 100;
    int c = price % 100;

    this->dollars = d;
    this->cents = c;
}

Price Price::substractPrice(Price p)
{
    int d = this->dollars - p.dollars;
    int c = this->cents - p.cents;

    if (d <= 0 && cents <= 0)
    {
        return Price("0.0");
    }
    else if (d >= 1 && cents < 0)
    {
        d = d - 1;
        c = 100 + c;
    }
    return Price(to_string(d) + "." + to_string(c));
}

bool Price::isPaid()
{
    if (this->dollars <= 0 && this->cents <= 0)
    {
        return true;
    }
    return false;
}

string Price::getPrice()
{
    return "$" + to_string(this->dollars) + "." + to_string(this->cents);
}

vector<string> Price::denomList()
{
    vector<string> denomList;

    int nominal[8] = {5, 10, 20, 50, 100, 200, 500, 1000};
    string denom[8] = {"5c",
                       "10c",
                       "20c",
                       "50c",
                       "$1",
                       "$2",
                       "$5",
                       "$10"};

    int priceNominal = this->dollars * 100 + this->cents;

    int pos = 7;
    while (pos >= 0 && priceNominal > 0)
    {
        int qty = priceNominal / nominal[pos];
        if (qty > 0)
        {
            if (qty == 1)
            {
                denomList.push_back(denom[pos]);
            }
            else
            {
                denomList.push_back(denom[pos] + "x" + to_string(qty));
            }
        }
        priceNominal %= nominal[pos];
        pos--;
    }

    return denomList;
}
