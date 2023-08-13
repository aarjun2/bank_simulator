#include "Jolly_Bank.h"


int main() {
	JollyBank my_Bank;
	ofstream outFile;
	outFile.open("BankTransOut.txt", std::ofstream::out | std::ofstream::trunc);
	my_Bank.process_transaction();
	my_Bank.display_tree();
	return 0;
}



