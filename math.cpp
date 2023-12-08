#include <iostream>

    namespace Variant1{
     
        typedef int count_t ;
        count_t student = 20;
    }
    
    int main () {
            //aritmatic OP
            using namespace Variant1 ;

            count_t student = 2;
            student = student + 1;
             student += 4;
             student++;
             student = student + Variant1::student;
             student += Variant1::student;


            //  XXXXXXXXXXXX

             student = student*student;
             student *= student;
             student = student * Variant1::student;
            
            const int sira = 18;
            const int student_bir_sira = 3;
            const int student_sum = student_bir_sira * sira;

            int student_sayisi;
            std::cout << "How many student in your class? : "<< sira*student_bir_sira << std::endl;
            std::cout << "4 Student get out in class  : " << std::endl;
            std::cout << "How many student in your class? : "<< sira*student_bir_sira -4 << std::endl;
            std::cout << "Half Student get out in class  : " << std::endl;
            std::cout << "How many student in your class? : "<< sira*student_bir_sira /2 << std::endl;
            
            // Exam result
           int corrrect = 20;
           int question = 25;
           double result = corrrect / (double)question *100;

           std::cout << "Your result is : " << result << std::endl;

            return 0;
    }