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

// Function to display inventory to the player
void displayInventory(const GameData& data) {
    std::cout << "Inventory:\n";
    std::cout << "Coins: " << data.inventory.coins << "\n";
    
    std::cout << "Weapons:\n";
    for (const auto& weaponPair : data.inventory.weapons) {
        const Weapon& weapon = weaponPair.second;
        std::cout << "  - Name: " << weapon.name << "\n";
        std::cout << "    Description: " << weapon.description << "\n";
        std::cout << "    Rarity: " << weapon.rarity << "\n";
        std::cout << "    Damage: " << weapon.damage << "\n";
        std::cout << "    Durability: " << weapon.durability.state << "/" << weapon.durability.max << "\n";
    }

    std::cout << "Resources:\n";
    for (const auto& resourcePair : data.inventory.resources) {
        std::cout << "  - " << resourcePair.first << ": " << resourcePair.second << "\n";
    }
}

int main() {
    GameData data;

    // Read existing data from JSON file
    readData("data.json", data);

    // Display the inventory to the player
    displayInventory(data);

    return 0;
}
