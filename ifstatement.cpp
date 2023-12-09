#include <iostream>
#include <cmath>

 namespace EnoSik
 {
    typedef int EnSik_t;

    EnSik_t EnoSik;
 }
 int main (){
        std::cout<<" Enonun Sik Boyu Kac Cm : "<<std::endl;
        std::cin>>EnoSik::EnoSik;

      if (
        EnoSik::EnoSik >= 10
      )
      {
        std::cout<<"Eno cevirsinde kendine soksun"<<std::endl;
      }
      else{
        std::cout<<"Eno her turlu sana giriyo aslanim"<<std::endl;
      }
      
}