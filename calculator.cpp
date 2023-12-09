#include <iostream>
#include <cmath>

    namespace calculator
        {
        typedef double calculatorD_t;
        typedef char calculatorC_t;

        calculatorC_t op;
        calculatorD_t nm1;
        calculatorD_t nm2;
        }

        int main(){

            using namespace calculator;


            std::cout<<"Enter your operator : "<<std::endl;
            std::cin>>op;
            
            std::cout<<"Enter your first number : "<<std::endl;
            std::cin>>nm1;

            std::cout<<"Enter your second number : "<<std::endl;
            std::cin>>nm2;

            switch(op)
            {
            case ('+'):
                
                std::cout<<"Your result is : "<<nm1 + nm2<<std::endl;
                break;
            case ('-'):
                std::cout<<"Your result is : "<<nm1 - nm2<<std::endl;
                break;
            case ('*'):
                std::cout<<"Your result is : "<<nm1 * nm2<<std::endl;
                break;
            case ('/'):
                std::cout<<"Your result is : "<<nm1 / nm2<<std::endl;
                break;
            case ('^'):
                std::cout<<"Your result is : "<<pow(nm1,nm2)<<std::endl;
                break;
            case ('%'):
                std::cout<<"Your result is : "<<fmod(nm1,nm2)<<std::endl;
                break;
            default:
                std::cout<<"Invalid operator"<<std::endl;
                break;
            }

        }