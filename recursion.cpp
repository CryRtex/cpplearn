#include "Core.h"
#include <iostream>
#include <algorithm>
using namespace std;

namespace Core {
    int myNumArray[5] = { 2, 3, 4, 7, 8 };
    int  PrintHelloWorld(int n)
    {
        if (n == 0)
            return myNumArray[0];  
        else if (n == 1)
            return myNumArray[1];  
        else if (n >= 5)
            return -1;  

        return myNumArray[n] + PrintHelloWorld(n - 1);
    }
    void PrintHelloWorl()
    {
        int result = PrintHelloWorld(4);  // Örneğin 4. indeksi toplamak
        std::cout << "Sonuç: " << result << std::endl;
    }
}
