// Banking Application



#include <iostream>

    void ShowBalance(double balance);
    double deposit();
    double withdraw(double balance);


int main(){

    int choice = 0;
    double balance = 0;

                do{
                                
                        std::cout <<"Hello Sikko Bank"<< std::endl;
                        std::cout <<"Please enter your choice"<< std::endl;
                        std::cout <<"1. Show Balance"<< std::endl;
                        std::cout <<"2. Deposit"<< std::endl;
                        std::cout <<"3. Withdraw"<< std::endl;
                        std::cout <<"4. Exit"<< std::endl;
                        std::cin >> choice;

                    switch(choice){
                       case 1: ShowBalance(balance);
                                break;
                        case 2:balance += deposit();
                                ShowBalance(balance);
                                break;
                        case 3:  balance -= withdraw(balance);
                                 ShowBalance(balance);
                                 break;
                        case 4:std::cout << "Thank you for using Sikko Bank" << std::endl;
                            break;
                                
                        default:
                        std::cout << "Invalid choice" << std::endl;
                    }
                
                } while (choice != 4);
    return 0;
}

     void ShowBalance(double balance){
        std::cout << "Your current balance is: " << balance << std::endl;
    }
    double deposit(){
         double amount = 0;
         std::cout << "Enter the amount you want to deposit: " << std::endl;
         std::cin >> amount;
        return amount;
    }   
    double withdraw(double balance){
        double amount = 0;
        std::cout << "Enter the amount you want to withdraw: " << std::endl;
        std::cin >> amount;
        return amount;
    }