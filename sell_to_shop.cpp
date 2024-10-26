// sell_to_shop.cpp
#include <iostream>
#include <fstream>
#include "game_data.hpp"

// Function to read data from JSON file
void readData(const std::string& filename, GameData& data) {
    std::ifstream file(filename);
    if (file) {
        cereal::JSONInputArchive archive(file);
        archive(data);
    } else {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
    }
}

void writeData(const std::string& filename, const GameData& data) {
    std::ofstream file(filename);
    cereal::JSONOutputArchive archive(file);
    archive(data);
}

void sellItem(GameData& data, const std::string& itemName) {
    auto weaponIt = data.inventory.weapons.find(itemName);
    if (weaponIt != data.inventory.weapons.end()) {
        int price = weaponIt->second.sell_price;
        data.inventory.coins += price;
        data.inventory.weapons.erase(weaponIt);
        std::cout << "Sold weapon: " << itemName << "\n";
    } else {
        auto resourceIt = data.inventory.resources.find(itemName);
        if (resourceIt != data.inventory.resources.end() && resourceIt->second > 0) {
            int price = data.shop.trade.items[itemName].sell_price;
            data.inventory.coins += price;
            data.inventory.resources[itemName] -= 1;
            std::cout << "Sold resource: " << itemName << "\n";
        } else {
            std::cout << itemName << " not in inventory.\n";
        }
    }
}

int main() {
    GameData data;
    readData("data.json", data);
    std::cout << "Enter the name of the item to sell: ";
    std::string itemName;
    std::getline(std::cin, itemName);
    sellItem(data, itemName);
    writeData("data.json", data);
    return 0;
}
