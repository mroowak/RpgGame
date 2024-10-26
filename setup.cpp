#include <iostream>
#include <fstream>
#include "game_data.hpp"

int main() {
    // Create GameData instance and populate with initial data
    GameData data;
    
    // Inventory initialization
    data.inventory.coins = 25;
    data.inventory.weapons["Stick"] = {"Stick", "A basic starter weapon.", "Common", 1, {10, 10}, 0, 0};
    data.inventory.resources["iron"] = 4;

    // Shop initialization
    data.shop.shelf.weapons["Small sword"] = {"Small sword", "Not the best weapon but great for beginners.", "Common", 5, {35, 35}, 15, 10};
    data.shop.shelf.weapons["Big sword"] = {"Big sword", "The swordman's dream.", "Rare", 15, {80, 80}, 40, 20};
    data.shop.trade.items["iron"] = {4, 3};
    data.shop.trade.items["gold"] = {8, 7};

    // Serialize to JSON and save in "data.json"
    std::ofstream file("data.json");
    cereal::JSONOutputArchive archive(file);
    archive(data);  // Save data to file

    std::cout << "Data saved to data.json" << std::endl;
    return 0;
}
