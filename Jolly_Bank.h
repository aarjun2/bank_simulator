/*
    JollyBank.h

    The .h file for JollyBank.cpp

    A Banking system that reads in a given file that it prompts the user for and proforms
    all the trasactions in the file assuming it's well made.

    Made by: Marcella, Arjun, Tumaris, Shumin

    Last Edited: 12/13/2022
*/

#include <queue>
#include <fstream>
#include "BST.h"

class JollyBank
{

public:

    JollyBank();

    //~JollyBank(); // this can call the BSTree decontructor.

    bool ReadObjectsFromFile(string fName, queue<string>& qu);

    void string_parser(string line, vector<string>& one_word);

    void askForFile();

    void process_transaction();

    void display_tree();


private:
    queue<string> my_queue;
    vector<string> test;
    BSTree my_tree;
    string inFile;
};
