#include <iostream>

    int main(){
            int number;
        
            srand(time(NULL)); // seed the random number generator  
        for(int i = 0; i < 10; i++)
        {
            
            number = rand() % (50 - 40 + 1) + 40; // generate a random number between 1 and 100
  
            std::cout<<  number <<std::endl;
        }
    

        return 0;
    }