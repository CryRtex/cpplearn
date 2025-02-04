#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sqlite3.h>

// Veri tabanından veri çekme fonksiyonu
std::vector<std::pair<int, std::string>> getDataFromDB() {
    sqlite3* db;
    sqlite3_open("database.db", &db);
    
    std::vector<std::pair<int, std::string>> data;
    sqlite3_stmt* stmt;
    std::string query = "SELECT id, role FROM customers";
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            data.emplace_back(id, role);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return data;
}

// Müşteri rollerine göre veriyi işle
std::map<std::string, std::vector<int>> processCustomerData(const std::vector<std::pair<int, std::string>>& data) {
    std::map<std::string, std::vector<int>> processedData;
    for (const auto& entry : data) {
        processedData[entry.second].push_back(entry.first);
    }
    return processedData;
}

// Sonuçları ekrana yazdırma
void outputData(const std::map<std::string, std::vector<int>>& data) {
    for (const auto& [role, ids] : data) {
        std::cout << "Role: " << role << " - Customers: ";
        for (int id : ids) {
            std::cout << id << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Adım 1: Veriyi çek
    std::vector<std::pair<int, std::string>> rawData = getDataFromDB();
    
    // Adım 2: Müşteri rollerine göre işle
    std::map<std::string, std::vector<int>> processedData = processCustomerData(rawData);
    
    // Adım 3: Sonuçları göster
    outputData(processedData);
    
    return 0;
}
