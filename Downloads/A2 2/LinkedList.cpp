#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
    count = 0;
}

void LinkedList::loadStock(string stockFile)
{
    ifstream myFile(stockFile);

    if (!myFile.is_open())
    {
        cerr << "Error opening " << stockFile << endl;
    }

    string line;
    while (getline(myFile, line))
    {
        istringstream iss(line);
        string fieldId, fieldName, fieldDescription, fieldPrice, fieldOnHand;
        getline(iss, fieldId, '|');
        getline(iss, fieldName, '|');
        getline(iss, fieldDescription, '|');
        getline(iss, fieldPrice, '|');
        getline(iss, fieldOnHand);

        Price newPrice(fieldPrice);

        Stock *newStock = new Stock();
        newStock->id = fieldId;
        newStock->name = fieldName;
        newStock->description = fieldDescription;
        newStock->price = newPrice;
        newStock->on_hand = stoi(fieldOnHand);

        this->insertNode(newStock);
    }
    myFile.close();

    cout << stockFile << " loaded." << endl;
}

void LinkedList::saveStock(string stockFile)
{
    ofstream myFile(stockFile);

    Node *temp = head;
    while (temp != nullptr)
    {
        myFile << temp->data->id << "|";
        myFile << temp->data->name << "|";
        myFile << temp->data->description << "|";
        myFile << temp->data->price.dollars << ".";
        myFile << temp->data->price.cents << "|";
        myFile << temp->data->on_hand << endl;

        temp = temp->next;
    }
    myFile.close();

    cout << stockFile << " saved." << endl;
}

void LinkedList::insertNode(Stock *data)
{
    Node *newNode = new Node(data);

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    this->count++;
}

void LinkedList::deleteNode(int position)
{
    Node *temp1 = head, *temp2 = nullptr;

    if (head == nullptr)
    {
        cout << "List empty." << endl;
        return;
    }

    if ((int)this->count < position)
    {
        cout << "Index out of range" << endl;
        return;
    }

    temp1 = head;
    if (position == 1)
    {
        head = head->next;
        delete temp1;
        return;
    }

    while (position-- > 1)
    {
        temp2 = temp1;
        temp1 = temp1->next;
    }

    temp2->next = temp1->next;

    delete temp1;
}

void LinkedList::showItemsList()
{
    Node *temp = head;

    if (head == nullptr)
    {
        cout << "Items Empty" << endl;
        return;
    }

    cout << left << setw(6) << "ID";
    cout << left << setw(40) << "|Name";
    cout << left << setw(12) << "|Available";
    cout << left << setw(12) << "|Price";
    cout << endl;

    for (int i = 0; i < 70; i++)
        cout << "-";
    cout << endl;

    while (temp != nullptr)
    {

        cout << left << setw(6) << temp->data->id;
        cout << left << setw(40) << "|" + temp->data->name;
        cout << left << setw(12) << "|" + temp->data->getAvailable();
        cout << left << setw(12) << "|" + temp->data->price.getPrice();
        cout << endl;
        temp = temp->next;
    }
}

void LinkedList::printList()
{
    Node *temp = head;

    // Check for empty list.
    if (head == nullptr)
    {
        cout << "List empty" << endl;
        return;
    }

    // Traverse the list.
    while (temp != nullptr)
    {
        cout << temp->data->id << " ";
        cout << temp->data->name << " ";
        cout << temp->data->description << " ";
        cout << temp->data->price.dollars << " ";
        cout << temp->data->price.cents << " ";
        cout << temp->data->on_hand << endl;
        temp = temp->next;
    }
}

string LinkedList::getNewStockId()
{
    int max_id = 0;
    Node *temp = head;

    while (temp != nullptr)
    {
        string node_id = temp->data->id;
        string numeric_part_str = node_id.substr(1);

        int numeric_part;
        istringstream(numeric_part_str) >> numeric_part;

        if (numeric_part > max_id)
        {
            max_id = numeric_part;
        }
        temp = temp->next;
    }

    max_id++;
    ostringstream new_id_stream;
    new_id_stream << "I" << setw(4) << setfill('0') << max_id;
    return new_id_stream.str();
}

pair<Node *, int> LinkedList::findById(string searchValue)
{
    Node *temp = head;
    int pos = 1;

    while (temp != nullptr)
    {
        string node_id = temp->data->id;
        if (node_id == searchValue)
        {
            return make_pair(temp, pos);
        }
        temp = temp->next;
        pos++;
    }

    // If not found
    return make_pair(nullptr, -1);
}

void LinkedList::resetAllStock()
{
    Node *temp = head;

    // Check for empty list.
    if (head == nullptr)
    {
        cout << "List empty" << endl;
        return;
    }

    // Traverse the list.
    while (temp != nullptr)
    {
        temp->data->resetStock();
        temp = temp->next;
    }
}

int LinkedList::getHeadOnHand()
{
    return (int)head->data->on_hand;
}

LinkedList::~LinkedList()
{
    Node *temp = head;

    while (temp != nullptr)
    {
        temp = temp->next;
    }

    cout << "LinkedList destructed" << endl;
}

void LinkedList::sortList()
{
    this->insertionSort();
}

void LinkedList::insertionSort()
{
    Node *sortedList = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
        Node *nextNode = current->next;
        addNode(&sortedList, current);
        current = nextNode;
    }
    head = sortedList;
}

void LinkedList::addNode(Node **head, Node *newNode)
{
    if (*head == nullptr || (*head)->data->name >= newNode->data->name)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        Node *current = *head;
        while (current->next != nullptr && current->next->data->name < newNode->data->name)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}