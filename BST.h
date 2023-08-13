/*
    BSTree.h

    The .h file for BSTree.cpp

    A binary search tree that hold Account objects and sorts them by the Account ID numbers

    Made by: Marcella, Arjun, Tumaris, Shumin

    Last Edited: 12/13/2022
*/

#include "Account.h"

class BSTree
{
private:        // needed to flip this because struct defintion needs to be here before we can use it in public function
    struct Node // alternate was to write the functions as private, but this makes more sense
    {
        Account* pAcct;
        Node* right;
        Node* left;
    };
    Node* root;

public:

    BSTree();

    ~BSTree();

    bool Insert(Account* acc);


    // retrieve object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool recrusive_retrieve(Node* r, int id, Account*& p) const;

    bool Retrieve(const int& id, Account*& p) const;

    // displays the contents of a tree
    void in_order(Node* r) const;

    void Display() const;


    void recursive_post_order(Node* r);

    void Empty();

    bool isEmpty() const;

};
