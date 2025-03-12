#include <iostream>

using namespace std;

class BankAccount {
	private:
		int balance;
		int  withdraw;
		int  deposit;
	public:
		void BankDetails() {
			balance = (1000);
			withdraw = (500);
			deposit = (1000);
		}
		friend void Balance(BankAccount);
};

void Balance(BankAccount account) {
	cout << "Balance: " << account.balance << endl;
    cout << "Withdraw: " << account.withdraw << endl;
    cout << "Deposit: " << account.deposit << endl;

}

int main() {
    BankAccount account;
    account.BankDetails();
	Balance(account);
	return 0;
}
