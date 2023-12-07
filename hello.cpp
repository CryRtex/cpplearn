#include <iostream>

int main()
{

    // Comment area in there but ı learning new things
    /* 2 sum command line 
    in etc
    */
    
    std::cout << "Hello, World!\n";
    std::cout << "Hello, World!\n";
   
   
    // Declare Variables 
     int testValue;
    int test2val;
    int value;

    testValue = 0;
    test2val = 2;
    value = test2val + testValue;

    std::cout << value << std::endl;
   
   // Test Double is it a up error 

    double testValue;
    double test2val;
    double value;
    
    test2val = 9.55;
    testValue = 0.55;
    
    value = test2val * testValue;

    std::cout << value << std::endl;
    

   // char type
 
   char onecase= 'a';
   //  char = 'b'; "error" please write some world char veriable
   char twocase= 'b';

    
    std::cout  << twocase << std::endl;
  
   //bool type 

    bool student = true;
    bool teacher = false;
    
    if (student== true)
    {
        std::cout << "Student" << std::endl;
    }
    else if (teacher == true)
    {
        std::cout << "Teacher" << std::endl;
    }
    else
    {
        std::cout << "Not Student or Teacher" << std::endl;
    }
   
   // const type the not change value
        
        const bool PI = 3.14; // Yes or No 
        const  double PI2 = 3.14; 
        const int screenrect = 1920 * 1080; // math cross 
        const char letter = 'a';  // not change 
        std::cout << PI <<" is there a other sit\n";
        std::cout << screenrect << std::endl;
        std::cout << letter << std::endl;
        std::cout << PI2 << std::endl;
       
    return 0;
}
