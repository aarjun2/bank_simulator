/*
    BSTree.cpp

    A binary search tree that hold Account objects and sorts them by the Account ID numbers

    Made by: Marcella, Arjun, Tumaris, Shumin

    Last Edited: 12/13/2022
*/

#include "BST.h"


/*
    BSTree():

    default contrucotr

    sets the root to nullptr.

    params: none
*/
BSTree::BSTree()
{
    root = nullptr;
}

/*
    ~BSTree():

    Decontructor:

    deconstructs the binary search tree

    params: none
*/
BSTree::~BSTree()
{
    Empty();
}

/*
    Insert():

    Inserts in a new Account object. Returns true is sucessful
    (the account doesn't already exist in the BSTree), else returns false.

    params: Account *acc

    returns: bool
*/
bool BSTree::Insert(Account* acc)
{
    Node* new_node = new Node;
    Node* temp = root;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->pAcct = acc;
    if (root == nullptr)
    {
        root = new_node;
    }
    else
    {
        while (temp != nullptr)
        {
            if (new_node->pAcct->get_id() < temp->pAcct->get_id() && (temp->left == nullptr))
            {
                temp->left = new_node;
                break;
            }
            else if (new_node->pAcct->get_id() < temp->pAcct->get_id())
            {
                temp = temp->left;
            }
            else if (new_node->pAcct->get_id() > temp->pAcct->get_id() && (temp->right == nullptr))
            {
                temp->right = new_node;
                break;
            }
            else if (new_node->pAcct->get_id() == temp->pAcct->get_id()) //added this if the account already exists
            {
                return false;
                break;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    return true;
}

/*
    recrusive_retrieve(Node *r, int id, Account *&p) const:

    retrives the given account using recursion. The Account is
    returned through the Account reference given to it, and true
    is returned if it's found. false if returned if it isn't found.

    params: (Node *r, int id, Account *&p)

    returns: none
*/
bool BSTree::recrusive_retrieve(Node* r, int id, Account*& p) const
{
    if (r != nullptr)
    {
        if (r->pAcct->get_id() == id)
        {
            p = r->pAcct;
            return true;
        }
        else if (id < r->pAcct->get_id())
        {
            return recrusive_retrieve(r->left, id, p);
        }
        else
        {
            return recrusive_retrieve(r->right, id, p);
        }
    }
    else
    {
        return false;
    }
}

/*
    Retrieve(const int &id, Account *&p)const:

    retrives the given account. The Account is
    returned through the Account reference given to it, and true
    is returned if it's found. false if returned if it isn't found.

    params: const int &id, Account *&p

    returns: bool
*/
bool BSTree::Retrieve(const int& id, Account*& p) const
{
    return recrusive_retrieve(root, id, p);
}

/*
    in_order(Node *r):

    cycles through all the accounts in order
    and tell them to print themselves out to the
    out file.

    params: Node *r

    returns: none
*/
void BSTree::in_order(Node* r) const
{
    if (r)
    {
        in_order(r->left);
        r->pAcct->display_tree_final();
        in_order(r->right);
    }
}

/*
    Display():

    displays the entire BSTree

    params: none

    returns: none
*/
void BSTree::Display() const
{
    ofstream outFile;
    outFile.open("BankTransOut.txt", ios::app);
    outFile << "Processing Done. Final Balances" << endl;
    in_order(root);
    outFile.close();
}

/*
    recursive_post_order(Node *r):

    Goes through the Nodes and deletes them
    recursively.

    params: Node *r

    returns: none
*/
void BSTree::recursive_post_order(Node* r)
{
    if (r != nullptr) {
        recursive_post_order(r->left);
        recursive_post_order(r->right);
        delete r;
    }
}

/*
    Empty():

    empties the BSTree.

    params: none

    returns: none
*/
void BSTree::Empty()
{
    recursive_post_order(root);
}

/*
    isEmpty():

    tells if the BSTree is empty

    params: none

    returns: none
*/
bool BSTree::isEmpty() const
{
    return (root == nullptr);
}
