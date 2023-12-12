#include <iostream>

    int main(){

        int number;
        int guess;
        int tries;
       
        srand(time(NULL)); // seed the random number generator  
        number = rand() % (50 - 40 + 1) + 40; // generate a random number between 1 and 100


        // Up is function in the class
        
        std::cout<<"Guess a number between 40 and 50"<<std::endl;
       
        do{
            std::cin>>guess;
            tries++;
            if(guess > number){
                std::cout<<"Too high"<<std::endl;
            }
            else if(guess < number){
                std::cout<<"Too low"<<std::endl;
            }
            else{
                std::cout<<"You guessed it in "<<tries<<" tries"<<std::endl;
            }
        }while(guess != number);
        return 0;
    }