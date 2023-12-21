#include <iostream>
#include <ctime>

int main() {
    std::time_t rawtime;
    std::time(&rawtime);

    // Use std::cout instead of printf
    std::cout << "The current local time is: " << std::ctime(&rawtime);

    return 0;
}