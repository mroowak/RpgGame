// shop.cpp
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

// Function to display shop items to the player
void displayShop(const GameData& data) {
    std::cout << "Shop Inventory:\n";

    // Displaying weapons
    std::cout << "Weapons:\n";
    for (const auto& weaponPair : data.shop.shelf.weapons) {
        const Weapon& weapon = weaponPair.second;
        std::cout << "  - Name: " << weapon.name << "\n";
        std::cout << "    Description: " << weapon.description << "\n";
        std::cout << "    Rarity: " << weapon.rarity << "\n";
        std::cout << "    Damage: " << weapon.damage << "\n";
        std::cout << "    Durability: " << weapon.durability.state << "/" << weapon.durability.max << "\n";
        std::cout << "    Buy Price: " << weapon.buy_price << "\n";
        std::cout << "    Sell Price: " << weapon.sell_price << "\n";
    }

    // Displaying resources with trade prices
    std::cout << "Resources:\n";
    for (const auto& tradePair : data.shop.trade.items) {
        std::cout << "  - " << tradePair.first << ": Buy Price: " << tradePair.second.buy_price
                  << ", Sell Price: " << tradePair.second.sell_price << "\n";
    }
}

int main() {
    GameData data;
    readData("data.json", data);
    displayShop(data);
    return 0;
}
