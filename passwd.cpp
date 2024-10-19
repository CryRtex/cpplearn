#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:'\",.<>?";

int charsetSize = sizeof(charset) - 1; 


string generatePassword(int length) {
    string password = "";
    
    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % charsetSize;  
        password += charset[randomIndex];       
    }

    return password;
}

int main() {
    srand(time(0));  
    
    int passwordLength;
    cout << "Parola uzunluğunu girin: ";
    cin >> passwordLength;

    string password = generatePassword(passwordLength);
    cout << "Üretilen parola: " << password << endl;

    return 0;
}
