#include <iostream>


int main (){
        std::string name [] = {"John", "James", "Jack", "Jill", "Jane"};
        
      /*  for (int i = 0; i < 5; i++){
                std::cout << name[i] << std::endl;
     */
               
                for (int i = 0; i < sizeof(name)/sizeof(std::string); i++){
                        std::cout << name[i] << std::endl;   
            
        }

}