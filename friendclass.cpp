#include <iostream>

using namespace std;

class BankAccount {
private:
    int balance;
    int withdraw;
    int deposit;

public:
    // Constructor to initialize the account with default values
    BankAccount() {
        balance = 1000;  // Başlangıç bakiyesi
        withdraw = 0;     // Başlangıç çekim miktarı
        deposit = 0;      // Başlangıç yatırma miktarı
    }

    // Friend class declaration
    friend class BankManager;
};

class BankManager {
public:
    // Method to display account details
    void displayAccountDetails(BankAccount& account) {
        cout << "Balance: " << account.balance << endl;
        cout << "Withdrawn: " << account.withdraw << endl;
        cout << "Deposited: " << account.deposit << endl;
    }

    // Method to deposit money
    void depositMoney(BankAccount& account, int amount) {
        account.deposit += amount;
        account.balance += amount;
    }

    // Method to withdraw money
    void withdrawMoney(BankAccount& account, int amount) {
        if (amount <= account.balance) {
            account.withdraw += amount;
            account.balance -= amount;
        } else {
            cout << "Yetersiz bakiye!" << endl;
        }
    }
};

int main() {
    BankAccount account; // BankAccount nesnesi oluşturuluyor
    BankManager manager; // BankManager nesnesi oluşturuluyor

    // Başlangıç durumu
    manager.displayAccountDetails(account);

    // Para yatırma işlemi
    manager.depositMoney(account, 500);
    cout << "500 birim yatırıldı." << endl;
    manager.displayAccountDetails(account);

    // Para çekme işlemi
    manager.withdrawMoney(account, 200);
    cout << "200 birim çekildi." << endl;
    manager.displayAccountDetails(account);

    // Yetersiz bakiye durumu
    manager.withdrawMoney(account, 2000); // Yetersiz bakiye
    manager.displayAccountDetails(account);

    return 0;
}
