#include "game_data.hpp"
#include "utility.hpp"

#include <iostream>
#include <fstream>

#include <map>
#include <random>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>

void addRandomItem(std::string rarity, GameData &data) {
    std::vector<std::string> foundItemsOfType;
    for (const auto &item : data.items) {
        if (item.second.rarity == rarity) {
            foundItemsOfType.push_back(item.first);
        }
    }
    if (!foundItemsOfType.empty()) {
        int randomIndex = Utility::getRandomNumber(0, foundItemsOfType.size() - 1);
        std::string randomItem = foundItemsOfType.at(randomIndex);

        if (data.player.inventory.items[randomItem].value == 0 || data.player.inventory.items.find(randomItem) == data.player.inventory.items.end()) {
            data.player.inventory.items[randomItem] = data.items[randomItem];
            data.player.inventory.items[randomItem].value = 1;
        } else {
            data.player.inventory.items[randomItem].value += 1;
        }
        std::cout << "You find " << data.items[randomItem].name << "!" << std::endl;
    }
    else {
        std::cout << "No items found." << std::endl;
    }
}

void lootChest(GameData &data) {
    int roll = Utility::getRandomNumber(1, 100);
    if (roll <= 50) { // common
        addRandomItem("Common",data);
    }
    else if (roll <= 75) { // uncommon
        addRandomItem("Unommon",data);
    }
    else if (roll <= 83) { // rare
        addRandomItem("Rare",data);
    }
    else {
        std::cout << "No items found." << std::endl;
    }
}

int main() {
    std::ifstream file("data/data.json");
    cereal::JSONInputArchive archive(file);

    GameData data;
    archive(data);

    lootChest(data);

    std::ofstream outFile("data/data.json");
    cereal::JSONOutputArchive outArchive(outFile);
    outArchive(data);

    return 0;
}
