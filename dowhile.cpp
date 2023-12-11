#include <iostream>
#include <string>


int main(){
 
       
       std::string name; 
            do {
            std::cout<< "Write the name ";
            std::cin>> name;

            }while ( name != "enes" && name != "Enes");

            std::cout<<name<< " orospu evladidir"<<std::endl;

            return 0;
            }
