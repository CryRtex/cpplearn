#include <iostream>
#include <vector>

// Try this typedef like was a char= int etc.
// typedef std::vector<std::pair<std::string , int>> pair_t; I have no idea in this section 

// typedef std::string text_t ; // is a basic QQ 
// typedef int my_age_t;
using my_age_t = int;
using text_t = std::string;

int main (){
    
    my_age_t age = 1990;
    text_t name = "Florentiy Orlov" /* text_t = string data type also std::string :D */ ;
    std::cout << name << ' ' << age << '\n'; // space is ' ' thats it 
    
} 