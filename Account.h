/*
    Account.h

    The .h file for Account.cpp.

    Holds the first name, last name, and ID of a bank accounts. Allong with the functions 
    to proform withdraw, deposite, transfer, and print history

    Made by: Marcella, Arjun, Tumaris, Shumin

    Last Edited: 12/13/2022
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

class Account
{
public:
      Account();
      Account(int val, string first, string last);
      int get_id() const;
      void deposit(int index, int money, string transc);
      bool can_be_withdrawn(int index, int money, string transc);
      void withdraw(int index, int money, string transc);
      void t_deposit(int index, int money, string transc);
      void t_withdraw(int index, int money, string transc);
      void parse_history(string str);
      void update_history(int index);
      void display_tree_final();
private:
      string first_name;
      string last_name;
      int id;
      int funds[10] = { 0 };
      string history[10];// used for keeping history so we dont have to do double array
      string subAccountNames[10] = { "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund" , "Value Fund", "Value Stock Index" };
      ofstream outFile;
};
