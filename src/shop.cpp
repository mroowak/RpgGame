#include <iostream>
#include <fstream>
#include "game_data.hpp"
#include "cereal/archives/json.hpp"

void showShop(GameData &data) {
    for (const auto &item : data.shop.items) {
        std::cout << item.second.name << std::endl;
        std::cout << "\tDescription: " << item.second.description << std::endl;
        std::cout << "\tBuy/Sell: " << item.second.buy_price << "/" << item.second.sell_price << std::endl;
    }
}

int main() {
    std::ifstream file("data/data.json");
    cereal::JSONInputArchive archive(file);

    GameData data;
    archive(data);

    showShop(data);
    return 0;
}
