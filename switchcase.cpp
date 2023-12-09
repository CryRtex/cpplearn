#include <iostream>

namespace Swi_t
{
    typedef char Swi_t;

    Swi_t grade;
}

int main(){

        using namespace Swi_t;

        std::cout<<"Enter your grade : "<<std::endl;
        std::cin>>grade;

        switch (grade)
        {
        case 'A':
            std::cout<<"Excellent"<<std::endl;
            break; 
        case 'B':
            std::cout<<"Good"<<std::endl;
            break; 
        case 'C':
            std::cout<<"Well done"<<std::endl;
            break; 
        case 'D':
            std::cout<<"You passed"<<std::endl;
            break; 
        case 'F':
            std::cout<<"Better try again"<<std::endl;   
            break; 
        default:
            std::cout<<"Invalid grade"<<std::endl;
        }
}