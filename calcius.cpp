#include <iostream>

    namespace calciuss 
        {
            double temp;
            char unit;
        }

            int main(){
                using namespace calciuss;

        
                        std::cout<<"Enter your unit :  C Or F Or K "<<std::endl;
                        std::cin>>unit; // unit = f or c
                        std::cout<<"Enter your temperature : "<<std::endl;
                        std::cin>>temp; // temp = 100

                        if(unit == 'c' || unit == 'C'){
                            std::cout<< "Fahreinheit Degree is : "<<(temp*1.8) + 32.0<<std::endl;
                            std::cout<< "Kelvin Degree is : "<< temp + 273.15<<std::endl;
                        }
                        else if(unit == 'f' || unit == 'F'){
                            std::cout<< "Calcius Degree is : "<< (temp-32)/1.8<<std::endl;
                            std::cout<< "Kelvin Degree is : "<< (temp-32)*(5/9) + 273.15<<std::endl;
                        }
                        else if(unit == 'k' || unit == 'K'){
                            std::cout<< "Calcius Degree is : "<< temp - 273.15<<std::endl;
                            std::cout<< "Fahreinheit Degree is : "<< (temp-273.15)*1.8 + 32.0<<std::endl;
                        }
                        else{
                            std::cout<<"Invalid unit"<<std::endl;
                        }
                        return 0;           
                    }




                    /* ***OpenAI Example Formula In Namespace*** **/
/*
#include <iostream>

namespace calciuss {
    double toFahrenheit(double celsius) {
        return celsius * 1.8 + 32.0;
    }

    double toCelsius(double fahrenheit) {
        return (fahrenheit - 32.0) / 1.8;
    }

    double toKelvinFromCelsius(double celsius) {
        return celsius + 273.15;
    }

    double toKelvinFromFahrenheit(double fahrenheit) {
        return (fahrenheit - 32.0) * 5.0 / 9.0 + 273.15;
    }

    double toCelsiusFromKelvin(double kelvin) {
        return kelvin - 273.15;
    }

    double toFahrenheitFromKelvin(double kelvin) {
        return (kelvin - 273.15) * 1.8 + 32.0;
    }
}

int main() {
    using namespace calciuss;

    double temp;
    char unit;

    std::cout << "Enter your unit :  C Or F Or K " << std::endl;
    std::cin >> unit;
    std::cout << "Enter your temperature : " << std::endl;
    std::cin >> temp;

    if (unit == 'c' || unit == 'C') {
        std::cout << "Fahrenheit Degree is : " << toFahrenheit(temp) << std::endl;
        std::cout << "Kelvin Degree is : " << toKelvinFromCelsius(temp) << std::endl;
    } else if (unit == 'f' || unit == 'F') {
        std::cout << "Celsius Degree is : " << toCelsius(temp) << std::endl;
        std::cout << "Kelvin Degree is : " << toKelvinFromFahrenheit(temp) << std::endl;
    } else if (unit == 'k' || unit == 'K') {
        std::cout << "Celsius Degree is : " << toCelsiusFromKelvin(temp) << std::endl;
        std::cout << "Fahrenheit Degree is : " << toFahrenheitFromKelvin(temp) << std::endl;
    } else {
        std::cout << "Invalid unit" << std::endl;
    }

    return 0;
}
*/