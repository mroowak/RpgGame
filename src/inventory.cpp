#include <iostream>
#include <fstream>
#include "game_data.hpp"
#include "cereal/archives/json.hpp"

void showInventory(GameData &data) {
    std::cout << "Coins: " << data.player.inventory.coins << std::endl;
    std::cout << "Items: " << std::endl;
    for (const auto &item : data.player.inventory.items) {
        std::cout << "\tName: " << item.second.name << std::endl;
        std::cout << "\t\tDescription: " << item.second.description << std::endl;
        std::cout << "\t\tRarity: " << item.second.rarity << std::endl;
        std::cout << "\t\tDamage: " << item.second.damage << std::endl;
        std::cout << "\t\tDurability: " << item.second.durability.state << "/" << item.second.durability.max << std::endl;
        std::cout << "\t\tBuy/Sell: " << item.second.buy_price << "/" << item.second.sell_price << std::endl;
        std::cout << "\t\tQuantity: " << item.second.value << std::endl;
    }
}

int main() {
    std::ifstream file("data/data.json");
    cereal::JSONInputArchive archive(file);

    GameData data;
    archive(data);

    showInventory(data);
    return 0;
}
