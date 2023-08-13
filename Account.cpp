/*
    Account.cpp

    Holds the first name, last name, and ID of a bank accounts. Allong with the functions
    to proform withdraw, deposite, transfer, and print history

    Made by: Marcella, Arjun, Tumaris, Shumin

    Last Edited: 12/13/2022

*/

#include "Account.h"

using namespace std;

/*
    Account();

    default contructor, sets ID to 0, and first and last name to empty strings

    params: none
*/
Account::Account()
{
    id = 0;
    first_name = "";
    last_name = "";
}

/*
    Account(int val, string first, string last):

    Contructors. Sets the ID, first name and last name

    params: int val, string first, string last
*/
Account::Account(int val, string first, string last)
{
    id = val;
    first_name = first;
    last_name = last;
}

/*
    get_id():

    returns the ID number

    prarams: none

    returns: int id
*/
int Account::get_id() const
{
    return id;
}

/*
    deposit(int index, int money, string transc):

    Adds the money amount given to the approiate account and adds that
    transaction to history. Only takes positive numbers and 0.

    params: int index, int money, string transc

    returns: none

*/
void Account::deposit(int index, int money, string transc)
{
    if (money >= 0) {
        funds[index] += money;
        history[index] += transc + ':';
    }
    else
    {
        outFile.open("BankTransOut.txt", ios::app);
        outFile << "ERROR: Negative numbers can not be deposited." << endl;

        outFile.close();
    }
}

/*
    can_be_withdrawn(int index, int money, string transc):

    Checks if the acount it's given has the money to withdraw the amount
    requested. If it doesn't but it's connected to an account that does, this function
    transfers the appripriate amount of money to the account (adding that tranfer to the history with the help
    of the passed in transc string) and returns true.

    If the acount doesn't have sufficent money and isn't
    connected to an account that can help it, this function returns false.

    params: int index, int money, string transc

    returns: bool
*/
bool Account::can_be_withdrawn(int index, int money, string transc)
{
    vector<string> temp;
    int temp_store = 0;
    string word = "";
    for (char x : transc)
    {
        if (x == ' ')
        {
            temp.push_back(word);
            word = "";
        }
        else
        {
            word += x;
        }
    }
    temp.push_back(word);
    if (index == 0)
    {
        temp_store = funds[0];
        int val = money - funds[0];
        if (val > funds[1])
        {
            return false;
        }
        else
        {
            funds[1] -= val;
            funds[0] += val;
            history[0] += temp[0] + ' ' + temp[1] + ' ' + to_string(temp_store);
            history[1] += temp[0] + ' ' + temp[1] + ' ' + to_string(val);
        }
    }
    if (index == 1)
    {
        temp_store = funds[1];
        int val = money - funds[1];
        if (val > funds[0])
        {
            return false;
        }
        else
        {
            funds[0] -= val;
            funds[1] += val;
            history[1] += temp[0] + ' ' + temp[1] + ' ' + to_string(temp_store);
            history[0] += temp[0] + ' ' + temp[1] + ' ' + to_string(val);
        }
    }
    if (index == 2)
    {
        temp_store = funds[2];
        int val = money - funds[2];
        if (val > funds[3])
        {
            return false;
        }
        else
        {
            funds[3] -= val;
            funds[2] += val;
            history[2] += temp[0] + ' ' + temp[1] + ' ' + to_string(temp_store);
            history[3] += temp[0] + ' ' + temp[1] + ' ' + to_string(val);
        }
    }
    if (index == 3)
    {
        temp_store = funds[3];
        int val = money - funds[3];
        if (val > funds[2])
        {
            return false;
        }
        else
        {
            funds[2] -= val;
            funds[3] += val;
            history[3] += temp[0] + ' ' + temp[1] + ' ' + to_string(temp_store);
            history[2] += temp[0] + ' ' + temp[1] + ' ' + to_string(val);
        }
    }
    if (index >= 4)
    {
        return false;
    }
    return true;
}

/*
    withdraw(int index, int money, string transc):

    Withdraws money from an account, if the account doesn't have
    enough and isn't connected to an account that has enough to help
    an error is thrown.

    params: (int index, int money, string transc)

    returns: none
*/
void Account::withdraw(int index, int money, string transc)
{
    outFile.open("BankTransOut.txt", ios::app);
    if (funds[index] >= money)
    {
        funds[index] -= money;
        history[index] += transc + ':';
    }
    else if (can_be_withdrawn(index, money, transc))
    {
        funds[index] -= money;
    }
    else
    {
        outFile << "ERROR: Not enough funds to withdraw" << " " << money << " " << "from " << last_name << " " << first_name << " " << subAccountNames[index] << endl;
    }
    outFile.close();
}

/*
    t_deposit(int index, int money, string transc):

    Adds the money amount that was transfered from another acount
    to the approiate account and adds that transaction to history.
    Only takes positive numbers and 0.

    params: int index, int money, string transc

    returns: none

*/
void Account::t_deposit(int index, int money, string transc)
{
    if (money >= 0) {
        funds[index] += money;
        history[index] += transc + ':';
    }
    else
    {
        outFile.open("BankTransOut.txt", ios::app);
        outFile << "ERROR: Negative numbers can not be deposited." << endl;
        outFile.close();
    }
}

/*
    t_withdraw(int index, int money, string transc):

    Withdraws money from an account to be transfered, if the account doesn't have
    enough and isn't connected to an account that has enough to help
    an error is thrown.

    params: (int index, int money, string transc)

    returns: none
*/
void Account::t_withdraw(int index, int money, string transc)
{
    outFile.open("BankTransOut.txt", ios::app);
    if (funds[index] >= money) {
        funds[index] -= money;
        history[index] += transc + ':';
    }
    else if (can_be_withdrawn(index, money, transc))
    {
        funds[index] -= money;
    }
    else
    {
        outFile << "ERROR: Not enough funds to withdraw to transfer" << " " << money << "from " << last_name << " " << first_name << " " << subAccountNames[index];
    }
    outFile.close();
}

void Account::parse_history(string str)
{
    string word = "";
    for (char x : str)
    {
        if (x == ':')
        {
            outFile << word << endl;
            word = "";
        }
        else
        {
            word += x;
        }
    }
    outFile << word << endl;
}

/*
    update_history(int index):

    Prints out the history of the accounts up the point this function
    is called. If the index is between 0 and 9 then only one of the sub fund accounts
    is printed. If the index is 10, all the accounts are printed.

    params: int index

    returns: none
*/
void Account::update_history(int index)
{
    outFile.open("BankTransOut.txt", ios::app);
    if (index == 10)
    {
        outFile << "Transaction History for " << last_name << " " << first_name << " " << "by Fund" << endl;
        for (int i = 0; i < 10; i++)
        {
            outFile << subAccountNames[i] << " :"
                << "$" << funds[i] << endl;
            parse_history(history[i]);
        }
    }
    else
    {
        outFile << "Transaction History for " << last_name << " " << first_name << " " << subAccountNames[index] << " : " << "$" << funds[index] << endl;
        outFile << subAccountNames[index] << " :"
            << "$" << funds[index] << endl;
        parse_history(history[index]);
    }
    outFile.close();
}

/*
    display_tree_final():

    Prints out the first name, last name, accounts ID,
    and all the subAccount names and ammounts in the main Acccount

    params: none

    returns: none
*/
void Account::display_tree_final()
{
    outFile.open("BankTransOut.txt",ios::app);
    outFile << last_name << " " << first_name << " "
        << "Account ID: " << id << endl;
    for (int i = 0; i < 10; i++)
    {
        outFile << subAccountNames[i] << " :"
            << "$" << funds[i] << endl;
    }
    outFile << endl;
    outFile.close();
}
