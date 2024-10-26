// game_data.hpp

#include <string>
#include <unordered_map>
#include "cereal/archives/json.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/string.hpp"

// Other necessary includes...

// Durability struct
struct Durability {
    int state;
    int max;

    template <class Archive>
    void serialize(Archive& archive) {
        archive(CEREAL_NVP(state), CEREAL_NVP(max));
    }
};

// Weapon struct
struct Weapon {
    std::string name;
    std::string description;
    std::string rarity;
    int damage;
    Durability durability;
    int buy_price;  // New
    int sell_price; // New

    template <class Archive>
    void serialize(Archive& archive) {
        archive(CEREAL_NVP(name), CEREAL_NVP(description), CEREAL_NVP(rarity),
                CEREAL_NVP(damage), CEREAL_NVP(durability), 
                CEREAL_NVP(buy_price), CEREAL_NVP(sell_price));  // Include new fields
    }
};

// TradeItem struct
struct TradeItem {
    int buy_price;
    int sell_price;

    template <class Archive>
    void serialize(Archive& archive) {
        archive(CEREAL_NVP(buy_price), CEREAL_NVP(sell_price));
    }
};

// Inventory struct
struct Inventory {
    int coins;
    std::unordered_map<std::string, Weapon> weapons;
    std::unordered_map<std::string, int> resources;

    template <class Archive>
    void serialize(Archive& archive) {
        archive(CEREAL_NVP(coins), CEREAL_NVP(weapons), CEREAL_NVP(resources));
    }
};

// Shop and Trade structs
struct Shop {
    struct Shelf {
        std::unordered_map<std::string, Weapon> weapons;
        
        template <class Archive>
        void serialize(Archive& archive) {
            archive(CEREAL_NVP(weapons));
        }
    } shelf;

    struct Trade {
        std::unordered_map<std::string, TradeItem> items;

        template <class Archive>
        void serialize(Archive& archive) {
            archive(CEREAL_NVP(items));
        }
    } trade;

    template <class Archive>
    void serialize(Archive& archive) {
        archive(CEREAL_NVP(shelf), CEREAL_NVP(trade));
    }
};

// GameData struct
struct GameData {
    Inventory inventory;
    Shop shop;

    template <class Archive>
    void serialize(Archive& archive) {
        archive(CEREAL_NVP(inventory), CEREAL_NVP(shop));
    }
};
