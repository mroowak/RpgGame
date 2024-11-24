#include <iostream>
#include <fstream>
#include "game_data.hpp"
#include "cereal/archives/json.hpp"

void buyItem(GameData &data, std::string &itemName) {
    // check if itemName is correct
    try {
        for (auto &item : data.shop.items) {
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
        if (err==1){
            std::cout << "There is no such item in this shop!" << std::endl;
            return;
        }
    }

    auto &item = data.shop.items.at(itemName);
    if (data.player.inventory.coins >= item.buy_price) {
        data.player.inventory.coins -= item.buy_price;
        if (data.player.inventory.items.at(itemName).value == 0 || data.player.inventory.items.find(itemName) == data.player.inventory.items.end()) {
            data.player.inventory.items.at(itemName) = item;
            data.player.inventory.items.at(itemName).value = 1;
        } else {
            data.player.inventory.items.at(itemName).value += 1;
        }
        std::cout << "Bought " << itemName << "!" << std::endl;
    } else {
        std::cout << "Not enough coins!" << std::endl;
    }
}

int main() {
    std::ifstream file("data/data.json");
    cereal::JSONInputArchive archive(file);

    GameData data;
    archive(data);

    std::string itemName;
    std::cout << "What item do you want to buy?: ";
    getline(std::cin, itemName);
    buyItem(data, itemName);

    std::ofstream outFile("data/data.json");
    cereal::JSONOutputArchive outArchive(outFile);
    outArchive(data);

    return 0;
}
