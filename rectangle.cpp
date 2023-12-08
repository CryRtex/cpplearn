#include <iostream>
#include <cmath>



        namespace testValue
        {
            typedef double distance_t;
            distance_t a ;
            distance_t b ;
            distance_t c ;
            // karekök içinde a2+b2=c 
        }


    int main ()
        {
                      
            
                    std::cout << "Please enter A side of rectangle : " <<  std::endl;
                    std::cin >> testValue::a;
                    std::cout << "Please enter B side of rectangle : " << std::endl;
                    std::cin >> testValue::b;
                    
                    // Basit Yolu

                   testValue::a = pow(testValue::a,2);
                    testValue::b = pow(testValue::b,2);
                    testValue::c = sqrt(testValue::a + testValue::b);
                    std::cout << "C side of rectangle is : " << testValue::c << std::endl;
                    
                    // Bu 3 satır yanlış çıktı veriyor std::sqrt en önce verilmesi gereken önce onu veriyor
                        std::cout << std::pow(testValue::a,2) , std::pow(testValue::b,2) , std::sqrt(testValue::a + testValue::b) << std::endl;
                        std::cout << std::pow(testValue::a, 2) << " " << std::pow(testValue::b, 2) << " " << std::sqrt(testValue::a + testValue::b) << std::endl;
                        std::cout << std::pow(testValue::a, 2) << " " << std::pow(testValue::b, 2) << " " << std::sqrt(testValue::a + testValue::b) << std::endl;
                    
                    // Bu piç doğru 
                    std::cout << "Answer is : "<< std::sqrt(std::pow(testValue::a, 2) + std::pow(testValue::b, 2)) << std::endl;


                   
            // Yapmaya çalıştığım

             std::cout << "Please enter A side of rectangle : " <<  std::endl;
             std::cin >> testValue::a;
             std::cout << "Please enter B side of rectangle : " << std::endl;
             std::cin >> testValue::b;
             std::cout << std::pow(testValue::a,2) << std::pow(testValue::b,2)<< std::sqrt(testValue::a + testValue::b) << std::endl;
            
            
            return 0;
        }
    
