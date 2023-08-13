/*
    JollyBank.cpp
*/

#include "Jolly_Bank.h"


JollyBank::JollyBank()
{
    inFile = "";
}

/*
    ReadObjectsFromFile(string fName, queue<string> &qu):

    Given the fileName and a queue reference, this function splits up the file
    line by line and gives it to the queue. Returns true if file is successfully read,
    returns false if not.

    params: string fName, queue<string> &qu

    returns: bool
*/
bool JollyBank::ReadObjectsFromFile(string fName, queue<string>& qu)
{
    ifstream inFile;
    vector<string> data;
    inFile.open(fName);
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            string line;
            getline(inFile, line);
            qu.push(line);
        }
        inFile.close();
    }
    else
    {
        cout << "File: " << fName << "not found" << endl;
    }
    return true;
}

/*
    string_parser(string line, vector<string> &one_word):

    Given a string and a vector reference this function splits up the string
    by spaces and puts each word into a slot in the vector. The vector is changed
    in the function so nothing is returned.

    parans: string line, vector<string> &one_word

    returns: none
*/
void JollyBank::string_parser(string line, vector<string>& one_word)
{
    for (int i = 0; i < line.length(); i++)
    {
        string temp = "";
        while (line[i] != ' ' && line[i] != '\n' && line[i] != '\t' && line[i] != '\r' && i < line.length())
        {
            temp += line[i];
            i++;
        }
        one_word.push_back(temp);
    }
}


void JollyBank::askForFile()
{
    cout << "Please enter the file you would like processed." << endl;
    cin >> inFile;
    cout << "Thank you!" << endl;
}

/*
    process_transaction():

    Using the file collected with askForFile, this function reads in the file and
    processes the transactions it asks for. It then runs all the processed transactions and
    prints them into an out file.

    params: none

    returns: none
*/
void JollyBank::process_transaction()
{
    askForFile();
    ReadObjectsFromFile(inFile, my_queue); // stores the entire line in queue (in directions)
    while (!my_queue.empty())
    { // I just did this to check need to remove later
        string_parser(my_queue.front(), test);
        string order = my_queue.front();
        // cout << test.front() << endl;// this will store the first element of all data which is what we need
        //  need to REMOVE just for testing
        char option = '\0';
        if (!test.empty()) {
            option = test.front()[0]; // since the character is techinally stored as a string we have to extract it
        }
        switch (option)
        {
        case 'O':
        {
            Account* temp_p = nullptr;
            // need to check if this account already exists
            if (my_tree.Retrieve(stoi(test[3]), temp_p))
            {
                ofstream outFile;
                outFile.open("BankTransOut.txt", ios::app);
                outFile << "ERROR: Account"
                    << " " << stoi(test[3]) << " "
                    << "is already open.Transaction refused." << endl;
                outFile.close();
                break;
            }
            else
            {
                /*cout << "first: " << test[1] << endl;
                cout << "last: " << test[2] << endl;
                cout << "ID: " << test[3] << endl;*/
                temp_p = new Account(stoi(test[3]), test[1], test[2]);
                my_tree.Insert(temp_p);
            }
        }
        break;
        case 'D':
        {
            int type_fund = test[1].back() - '0'; // doing this to convert into int
            test[1].pop_back();                   // popped out the last type of fund
            int id_deposit = stoi(test[1]);       // converted id to string
            Account* temp = nullptr;
            my_tree.Retrieve(stoi(test[1]), temp);          // retrived the account at id
            temp->deposit(type_fund, stoi(test[2]), order); // deposited amount
        }
        break;
        case 'W':
        {
            int type_fund = test[1].back() - '0'; // doing this to convert into int
            test[1].pop_back();                   // popped out the last type of fund
            int id_deposit = stoi(test[1]);       // converted id to string
            Account* temp = nullptr;
            my_tree.Retrieve(stoi(test[1]), temp);           // retrived the account at id
            temp->withdraw(type_fund, stoi(test[2]), order); // withdrawed amount
        }                                                    // need to handle negatives, easy fix
        break;
        case 'T':
        {
            int ind_1 = test[1].back() - '0';
            int ind_2 = test[3].back() - '0';
            test[1].pop_back();
            test[3].pop_back();
            string acc_1 = test[1];
            string acc_2 = test[3];

            Account* account_1 = nullptr;
            Account* account_2 = nullptr;
            my_tree.Retrieve(stoi(acc_1), account_1);
            my_tree.Retrieve(stoi(acc_2), account_2);
            if (account_1 == nullptr)
            {
                ofstream outFile;
                outFile.open("BankTransOut.txt", ios::app);
                outFile << "ERROR: Account"
                    << " " << stoi(acc_1) << " "
                    << "not found.Transferal refused." << endl;
                outFile.close();
                break;
            }
            if (account_2 == nullptr)
            {
                ofstream outFile;
                outFile.open("BankTransOut.txt", ios::app);
                outFile << "ERROR: Account"
                    << " " << stoi(acc_2) << " "
                    << "not found.Transferal refused." << endl;
                outFile.close();
                break;
            }
            account_1->t_withdraw(ind_1, stoi(test[2]), order);
            account_2->t_deposit(ind_2, stoi(test[2]), order);
        }
        break;
        case 'H': // two variations one with all funds and one with specific fund
        {
            int index = 0;
            Account* temp = nullptr;
            if (test[1].length() == 4)
            {
                index = 10;
                my_tree.Retrieve(stoi(test[1]), temp);
                temp->update_history(index);
            }
            else
            {
                index = test[1].back() - '0';
                test[1].pop_back();
                my_tree.Retrieve(stoi(test[1]), temp);
                temp->update_history(index);
            }
        }
        break;
        }
        test.clear();
        my_queue.pop();
    }
}

/*
    display_tree():
    displays all the open accounts help int the bindary Search Tree.

    params: none

    returns: none
*/
void JollyBank::display_tree()
{
    my_tree.Display();
}