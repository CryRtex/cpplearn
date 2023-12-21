/*
#include <iostream>
#include <cstdlib>  // Include the cstdlib header for std::rand()
#include <ctime>

int main() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::cout << "Write some code here" << std::endl;
    // Define an array of numbers
    int numbers[] = {10, 20, 30, 40, 50};

    // Determine the size of the array
    int arraySize = sizeof(numbers) / sizeof(numbers[0]);

    // Generate a random index to select a number from the array
    int randomIndex = std::rand() % arraySize;

    // Print the randomly selected number
    std::cout << "The machine selected: " << numbers[randomIndex] << std::endl;

    return 0;
}
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Prompt the user to enter values for the array
    std::cout << "Enter " << " numbers for the array:" << std::endl;

    // Define an array of numbers
    const int arraySize = 5;  // Assuming an array size of 5
    int numbers[arraySize];

    // Accept user input for each element of the array
    for (int i = 0; i < arraySize; ++i) {
        std::cout << "Enter value for element " << i << ": ";
        std::cin >> numbers[i];
    }

    // Generate a random index to select a number from the array
    int randomIndex = std::rand() % arraySize;

    // Print the randomly selected number
    std::cout << "The machine selected: " << numbers[randomIndex] << std::endl;

    return 0;
}

