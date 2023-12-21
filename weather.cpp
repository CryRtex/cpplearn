#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    // Initialize cURL
    CURL* curl = curl_easy_init();

    if (curl) {
        // OpenWeatherMap API URL (replace YOUR_API_KEY with your actual API key)
        const char* url = "http://api.openweathermap.org/data/2.5/weather?q=CityName&appid=YOUR_API_KEY";

        // Set the cURL options
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Response data
        std::string response;

        // Perform the cURL request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Weather data received:\n" << response << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize cURL." << std::endl;
    }

    return 0;
}
