#include <iostream>
#include <fstream>
#include "game_data.hpp"
#include "cereal/archives/json.hpp"

int main() {
    GameData data;
    data.initializeDefaults();
    
    std::ofstream file("data/data.json");
    cereal::JSONOutputArchive archive(file);
    archive(data);

    std::cout << "Game data initialized in data.json" << std::endl;
    return 0;
}
