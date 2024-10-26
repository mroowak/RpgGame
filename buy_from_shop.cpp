// buy_from_shop.cpp
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

void buyItem(GameData& data, const std::string& itemName) {
    auto weaponIt = data.shop.shelf.weapons.find(itemName);
    if (weaponIt != data.shop.shelf.weapons.end()) {
        int price = weaponIt->second.buy_price;
        if (data.inventory.coins >= price) {
            data.inventory.coins -= price;
            data.inventory.weapons[itemName] = weaponIt->second;
            std::cout << "Bought weapon: " << itemName << "\n";
        } else {
            std::cout << "Not enough coins to buy " << itemName << "\n";
        }
    } else {
        auto tradeIt = data.shop.trade.items.find(itemName);
        if (tradeIt != data.shop.trade.items.end()) {
            int price = tradeIt->second.buy_price;
            if (data.inventory.coins >= price) {
                data.inventory.coins -= price;
                data.inventory.resources[itemName] += 1;
                std::cout << "Bought resource: " << itemName << "\n";
            } else {
                std::cout << "Not enough coins to buy " << itemName << "\n";
            }
        } else {
            std::cout << itemName << " not available in the shop.\n";
        }
    }
}

int main() {
    GameData data;
    readData("data.json", data);
    std::cout << "Enter the name of the item to buy: ";
    std::string itemName;
    std::getline(std::cin, itemName);
    buyItem(data, itemName);
    writeData("data.json", data);
    return 0;
}
