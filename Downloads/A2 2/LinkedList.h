#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void loadStock(string stockFile);
    void saveStock(string stockFile);

    void insertNode(Stock *data);
    void deleteNode(int position);
    void showItemsList();
    void resetAllStock();
    void printList();
    void sortList();

    int getHeadOnHand();
    string getNewStockId();
    pair<Node *, int> findById(string searchValue);

private:
    Node *head;
    unsigned count;

    void insertionSort();
    void addNode(Node **head, Node *newNode);
};

#endif // LINKEDLIST_H
