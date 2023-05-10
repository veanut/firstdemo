#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "LinkedList.h"
#include "Coin.h"
using namespace std;

string stockFile;
string coinsFile;
LinkedList myStock;
vector<Coin> myCoin;

void mainMenu();
void displayItemMenu();
void purchaseItemMenu();
void saveAndExitMenu();
void addItemMenu();
void removeItemMenu();
void resetStockCountMenu();
void resetCoinCountMenu();
void displayCoinMenu();
void abortMenu();

void loadCoins();
void saveCoins();

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        stockFile = argv[1];
        coinsFile = argv[2];

        myStock.loadStock(stockFile);
        myStock.sortList();
        loadCoins();

        mainMenu();
    }
    else
    {
        cout << "No data loaded." << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void mainMenu()
{
    cout << endl;
    cout << "Main Menu:" << endl;
    cout << "\t1. Display Items" << endl;
    cout << "\t2. Purchase Items" << endl;
    cout << "\t3. Save and Exit" << endl;

    cout << "Administrator Only Menu:" << endl;
    cout << "\t4. Add Item" << endl;
    cout << "\t5. Remove Item" << endl;
    cout << "\t6. Display Coins" << endl;
    cout << "\t7. Reset Stock" << endl;
    cout << "\t8. Reset Coins" << endl;
    cout << "\t9. Abort Program" << endl;

    cout << "Select your option (1-9): ";
    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        displayItemMenu();
        break;
    case 2:
        purchaseItemMenu();
        break;
    case 3:
        saveAndExitMenu();
        break;
    case 4:
        addItemMenu();
        break;
    case 5:
        removeItemMenu();
        break;
    case 6:
        displayCoinMenu();
        break;
    case 7:
        resetStockCountMenu();
        break;
    case 8:
        resetCoinCountMenu();
        break;
    case 9:
        abortMenu();
        break;

    default:
        exit(EXIT_FAILURE);
    }
}

void displayItemMenu()
{
    cout << endl;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    myStock.showItemsList();

    mainMenu();
}

void purchaseItemMenu()
{
    cout << endl;
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;

    string searchValue;
    cout << "Please enter the id of the item you wish to purchase: ";
    getline(cin, searchValue);

    pair<Node *, int> searchResult = myStock.findById(searchValue);

    if (searchResult.first != nullptr)
    {
        cout << "You have selected \"" << searchResult.first->data->name << " - " << searchResult.first->data->description << "\" This will cost you " << searchResult.first->data->price.getPrice() << endl;
        cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
        cout << "Press enter or ctrl-d on a new line to cancel this purchase: " << endl;

        int nominal[8] = {5, 10, 20, 50, 100, 200, 500, 1000};
        Price price = searchResult.first->data->price;

        bool isPaid = false;
        while (!isPaid)
        {
            cout << "You still need to give us " << price.getPrice() << ": ";
            int paid;
            cin >> paid;

            Price paidPrice(paid);

            bool found = false;
            if (end(nominal) == find(begin(nominal), end(nominal), paid))
            {
                found = true;
            }

            if (found)
            {
                Price temp = price.substractPrice(paidPrice);

                if (temp.isPaid())
                {
                    paidPrice = paidPrice.substractPrice(price);
                    cout << "Here is your Meat Pie and your change of " << paidPrice.getPrice();

                    vector<string> changes = paidPrice.denomList();
                    for (auto &element : changes)
                    {
                        cout << element << " ";
                    }
                    cout << endl;

                    isPaid = true;
                }
                else
                {
                    price = temp;
                }
            }
            else
            {
                cout << "Error:" << paidPrice.getPrice() << " is not a valid denomination of money. Please try again." << endl;
            }
        }
    }
    else
    {
        cout << searchValue << " not found." << endl;
    }

    mainMenu();
}

void saveAndExitMenu()
{
    cout << endl;
    cout << "Save and Exit" << endl;
    cout << "-------------" << endl;
    myStock.saveStock(stockFile);
    saveCoins();
}

void addItemMenu()
{
    cout << endl;
    cout << "Add Item" << endl;
    cout << "-------------" << endl;

    string newId = myStock.getNewStockId();
    cout << "The id of the stock will be: " << newId << endl;

    string newName;
    cout << "Enter the item name: ";
    getline(cin, newName);

    string newDescription;
    cout << "Enter the item description: " << endl;
    getline(cin, newDescription);

    string price_str;
    cout << "Enter the price for the item: " << endl;
    getline(cin, price_str);
    Price newPrice(price_str);

    Stock *newStock = new Stock();
    newStock->id = newId;
    newStock->name = newName;
    newStock->description = newDescription;
    newStock->price = newPrice;

    myStock.insertNode(newStock);

    cout << "This item \"" << newName << " - " << newDescription << "\" has now been added to menu." << endl;
    mainMenu();
}

void removeItemMenu()
{
    cout << endl;
    cout << "Remove Item" << endl;
    cout << "-------------" << endl;

    string searchValue;
    cout << "Enter the item id of the item to remove from the menu: ";
    getline(cin, searchValue);

    pair<Node *, int> searchResult = myStock.findById(searchValue);

    if (searchResult.first != nullptr)
    {
        cout << "\"" << searchResult.first->data->id << " - " << searchResult.first->data->name << " - " << searchResult.first->data->description << "\" has been removed from the system." << endl;
        myStock.deleteNode(searchResult.second);
    }
    else
    {
        cout << searchValue << " not found." << endl;
    }
    mainMenu();
}

void resetStockCountMenu()
{
    cout << endl;
    cout << "Reset Stock Count" << endl;
    cout << "-----------------" << endl;

    myStock.resetAllStock();

    cout << "All stock has been reset to the default level of " << myStock.getHeadOnHand() << endl;
    mainMenu();
}

void resetCoinCountMenu()
{
    cout << endl;
    cout << "Reset Coin Count" << endl;
    cout << "----------------" << endl;

    for (auto &element : myCoin)
    {
        element.resetCoinQuantity();
    }

    cout << "All coins have been reset to the default level of " << myCoin[0].count << endl;
    mainMenu();
}

void displayCoinMenu()
{
    cout << endl;
    cout << "Coins Summary" << endl;
    cout << "-------------" << endl;

    cout << left << setw(15) << "Denomination";
    cout << left << setw(1) << "|";
    cout << left << setw(8) << "Count";
    cout << endl;

    for (int i = 0; i < 24; i++)
        cout << "-";
    cout << endl;

    for (auto &element : myCoin)
    {
        cout << left << setw(15) << element.denom;
        cout << left << setw(1) << "|";
        cout << right << setw(8) << element.count;
        cout << endl;
    }

    mainMenu();
}

void abortMenu()
{
    exit(EXIT_FAILURE);
}

void loadCoins()
{
    ifstream file(coinsFile);

    if (!file.is_open())
    {
        cerr << "Error opening " << coinsFile << endl;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string fieldDenomination, fieldQuantity;
        getline(iss, fieldDenomination, ',');
        getline(iss, fieldQuantity);

        int denom = stoi(fieldDenomination);
        int qty = stoi(fieldQuantity);

        Coin newCoin;
        newCoin.count = qty;
        switch (denom)
        {
        case 1000:
            newCoin.denom = TEN_DOLLARS;
            break;
        case 500:
            newCoin.denom = FIVE_DOLLARS;
            break;
        case 200:
            newCoin.denom = TWO_DOLLARS;
            break;
        case 100:
            newCoin.denom = ONE_DOLLAR;
            break;
        case 50:
            newCoin.denom = FIFTY_CENTS;
            break;
        case 20:
            newCoin.denom = TWENTY_CENTS;
            break;
        case 10:
            newCoin.denom = TEN_CENTS;
            break;
        case 5:
            newCoin.denom = FIVE_CENTS;
            break;
        }

        myCoin.push_back(newCoin);
    }
    cout << coinsFile << " loaded." << endl;
}

void saveCoins()
{
    ofstream myFile(coinsFile);

    int denom_nominal[8] = {5, 10, 20, 50, 100, 200, 500, 1000};

    for (auto &element : myCoin)
    {
        myFile << denom_nominal[element.denom] << "," << element.count << endl;
    }
    myFile.close();

    cout << coinsFile << " saved." << endl;
}
