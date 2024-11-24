#include <iostream>
#include <fstream>
#include "game_data.hpp"
#include "cereal/archives/json.hpp"

void sellItem(GameData &data, std::string itemName) {
    // check if itemName is correct
    try {
        for (auto &item : data.player.inventory.items) {
            if (item.first == itemName) {
                throw 0;
                break;
            } else if (item.second.name == itemName) {
                itemName = item.first;
                throw 0;
                break;
            }
        }
        throw 1;
    } catch (int err) {
        if (err==1) {
            std::cout << "You don't have such item!" << std::endl;
            return;
        }
    }
    Item item = data.player.inventory.items.at(itemName);
    data.player.inventory.coins += item.sell_price;
    int quan = data.player.inventory.items.at(itemName).value - 1;
    if (data.player.inventory.items.at(itemName).value == 1) {
        data.player.inventory.items.erase(itemName);
    } else {
        data.player.inventory.items.at(itemName).value -= 1;
    }
    std::cout << "Sold " << itemName << "! You now have " << quan << " " << itemName << std::endl;
}

int main() {
    std::ifstream file("data/data.json");
    cereal::JSONInputArchive archive(file);

    GameData data;
    archive(data);

    std::string itemName;
    std::cout << "What item do you want to sell?: ";
    getline(std::cin, itemName);
    sellItem(data, itemName);

    std::ofstream outFile("data/data.json");
    cereal::JSONOutputArchive outArchive(outFile);
    outArchive(data);

    return 0;
}
