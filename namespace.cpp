// This folder ı am learning namespace

#include <iostream>
#include <string>


    namespace test
    {
        int value = 5;  
        std::string greeting = "Hello"; // string data type always use std:: please attention in there :D 
    }

    namespace second
    {
        int value = 6;
        std::string greeting = "Hi";
    }

int main() {
    // using namespace  test ; 
    // second method in using namespace <<Name>>
    std::cout << "Hello I am learn a new path!\n";
    std::cout << "Today ı am learning some namespaces and how could ı use this shit :d \n";
    std::cout <<  test::value << std::endl <<  test::greeting << std::endl;
    std::cout << second::value << std::endl<< second::greeting;
 }