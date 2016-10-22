#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


class hashTable {

private:
    static const int tableSize = 4;
    struct item {
        string name;
        string drink;
        item* next;
    };

    item* MyHashTable[tableSize]; // creating a hash table (array of linked lists)

public:

    // constructor
    hashTable() {
        for ( int i = 0; i < tableSize; i++ ) {
            MyHashTable[i] = new item;
            MyHashTable[i]->name = "empty";
            MyHashTable[i]->drink = "empty";
            MyHashTable[i]->next = NULL;
        }// end for loop
    }// end constructor

    // hashing function
    int Hash(string key) {
        int theHash = 0;
        int index = key.length();

        for (unsigned int i = 0; i < key.length(); i++ ) {
            theHash = ( theHash + (int)key.at(i) ) * 18; // random modifier
        }// end for

        index = theHash % tableSize;
        //cout << "Key " << key << " hashes to index " << index << endl;

        return index;
    }// end function Hash

    void AddItem(string name, string drink) {
        int index = Hash(name);
        if ( MyHashTable[index]->name == "empty"){
            // index is unused
            MyHashTable[index]->name = name;
            MyHashTable[index]->drink = drink;
        } else {
            // index is in use

            // create item for end of list
            item* n = new item;
            n->name = name;
            n->drink = drink;
            n->next = NULL;

            // attach item to end of list at correct index
            item* ptr = MyHashTable[index];
            while ( ptr->next != NULL) {
                ptr = ptr->next;
            }// end while

            ptr->next = n;// attach to end of list
        }// end if
    }// end addItem function

    int NumberOfItemsInIndex(int index) {

        item* ptr = MyHashTable[index];// point to beginning of list

        if ( ptr->name == "empty") {
            return 0;
        }

        int counter = 1;
        while ( ptr->next != NULL ) {
            counter++;
            ptr = ptr->next;
        }// end while

        return counter;
    }// end NumberOfItemsInIndex function

    void PrintTable() {
        int num;
        for (int i = 0; i < tableSize; i++ ) {
            num = NumberOfItemsInIndex(i);
            if (num > 1) {
                PrintItemsInIndex(i);
            } else {
                cout << "\tIndex " << i << endl;
                cout << "------------------" << endl;
                cout << "Name: " << MyHashTable[i] -> name << endl;
                cout << "Drink: " << MyHashTable[i] -> drink << endl;
                cout << "------------------" << endl;
            }// end if-else
        }// end for loop
    }// end function

    void PrintItemsInIndex (int index) {
        item* ptr = MyHashTable[index];

        if (ptr->name == "empty") {
            cout << "Index " << index << " is empty" << endl;
        } else {
            cout << "\tIndex " << index << endl;
            while (ptr != NULL) {
                cout << "------------------" << endl;
                cout << "Name: " << ptr->name << endl;
                cout << "Drink: " << ptr->drink << endl;
                cout << "------------------" << endl;
                ptr = ptr->next;// advance through list
            }// end while
        }// end if-else
    }// end PrintItemsInIndex function

    void FindDrink (string name) {
        int index = Hash(name);
        item* ptr = MyHashTable[index];//ptr at beginning of list
        if (ptr->name == "empty") {
            // list is empty
            cout << name << " is not in the Hash Table." << endl;
        } else {
            // list is not empty
            bool foundName = false;
            while (ptr != NULL && !foundName) {
                if (ptr->name == name) {
                    foundName = true;
                    cout << "Drink: " << ptr->drink << endl;
                }// end if
                ptr = ptr->next;
            }// end while
            if (!foundName)
                cout << name << " is not in the Hash Table." << endl;
        }// if else
    }// end FindDrink function

    void RemoveItem(string name) {
        int index = Hash(name);
        item* ptr = MyHashTable[index];// create new item

        bool itemFound = false;
        if (ptr->name == "empty") {
            cout << "Cannot delete, " << name << " is not in Hash Table" << endl;
        } else {
            // index is not empty
            if ( ptr->name == name ) {
                // item is found first in list
                if (ptr->next == NULL){
                    //is the only item in index
                    ptr->name = "empty";
                    ptr->drink = "empty";
                    cout << name << " was removed from the Hash Table." << endl;
                } else {
                    // there are multiple items at index

                    ptr->name = ptr->next->name;
                    ptr->drink= ptr->next->drink;

                    item* delPtr = ptr->next;
                    ptr->next = ptr->next->next;// unlink desired item from chain
                    delete delPtr;
                    cout << name << " has been deleted from the Hash Table" << endl;
                }// end if else

            } else {
                // item is not first in list
                while (ptr->next != NULL && !itemFound) {
                    // not at end of list
                    if (ptr->next->name == name) {
                        itemFound = true;
                        item* delPtr = ptr->next;
                        ptr->next = ptr->next->next; // unlink desired item
                        delete delPtr;// delete desired item
                        cout << name << " has been deleted from the Hash Table" << endl;
                    } else {
                        // advance through list by one
                        ptr = ptr->next;
                    }
                }// end while
                if (!itemFound)
                    cout << "Cannot delete, " << name << " is not in Hash Table" << endl;
            }// end if-else
        }// end if-else
    }// end function
};// end hashTable class


int main()
{
    hashTable myHashTable;

    myHashTable.PrintTable();
    return 0;
}
