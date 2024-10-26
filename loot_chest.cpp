#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
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

// Function to simulate opening a loot chest
void openLootChest(GameData& data) {
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed random number generator
    int lootChance = std::rand() % 100; // Random number between 0 and 99

    if (lootChance < 50) { // 50% chance to receive nothing
        std::cout << "You found nothing!\n";
    } else if (lootChance < 85) { // 35% chance to receive iron (50% - 85%)
        int ironAmount = std::rand() % 5 + 1; // Random amount of iron (1-5)
        data.inventory.resources["iron"] += ironAmount;
        std::cout << "You found " << ironAmount << " iron!\n";
    } else { // 15% chance to receive gold
        int goldAmount = std::rand() % 2 + 1; // Random amount of gold (1-2)
        data.inventory.resources["gold"] += goldAmount;
        std::cout << "You found " << goldAmount << " gold!\n";
    }
}

int main() {
    GameData data;
    readData("data.json", data);
    
    openLootChest(data); // Open the loot chest and give loot
    writeData("data.json", data); // Save the updated inventory

    return 0;
}
