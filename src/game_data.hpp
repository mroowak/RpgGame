#include <cereal/types/unordered_map.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>

#include <cereal/archives/json.hpp>

#include <fstream>
#include <string>
#include <map>
#include <unordered_map>

struct Item
{
    std::string name;
    std::string description;
    std::string rarity;
    int damage;

    struct Durability
    {
        int state;
        int max;

        template <class Archive>
        void serialize(Archive &ar)
        {
            ar(CEREAL_NVP(state), CEREAL_NVP(max));
        }
    } durability;

    int buy_price;
    int sell_price;
    int value;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(CEREAL_NVP(name), CEREAL_NVP(description), CEREAL_NVP(rarity),
           CEREAL_NVP(damage), CEREAL_NVP(durability),
           CEREAL_NVP(buy_price), CEREAL_NVP(sell_price), CEREAL_NVP(value));
    }
};

struct Inventory
{
    int coins;
    std::unordered_map<std::string, Item> items;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(CEREAL_NVP(coins), CEREAL_NVP(items));
    }
};

struct Stats
{
    int hp;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(CEREAL_NVP(hp));
    }
};

struct Player
{
    Stats stats;
    Inventory inventory;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(CEREAL_NVP(stats), CEREAL_NVP(inventory));
    }
};

struct ShortItems
{
    std::unordered_map<std::string, int> items;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(CEREAL_NVP(items));
    }
};

struct Players : ShortItems
{
    int coins;
    Stats stats;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(CEREAL_NVP(items), CEREAL_NVP(stats), CEREAL_NVP(coins));
    }
};

struct GameData
{
    Player player;
    Inventory shop;
    std::unordered_map<std::string, Item> items;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(CEREAL_NVP(player), CEREAL_NVP(shop), CEREAL_NVP(items));
    }

    void initializeDefaults()
    {
        std::ifstream file_items("config/items.json");
        std::ifstream file_players("config/players.json");
        std::ifstream file_shops("config/shops.json");

        // Check if files are open
        if (!file_items.is_open() || !file_players.is_open() || !file_shops.is_open())
        {
            throw std::runtime_error("Error opening one of the configuration files.");
        }

        // Local data structures for deserialization
        std::unordered_map<std::string, Item> loadedItems;
        std::unordered_map<std::string, Players> loadedPlayers;
        std::unordered_map<std::string, ShortItems> loadedShops;

        // Deserialize items
        try
        {
            cereal::JSONInputArchive archive_items(file_items);
            archive_items(cereal::make_nvp("items", loadedItems));
        }
        catch (const cereal::Exception &e)
        {
            throw std::runtime_error(std::string("Error reading items.json: ") + e.what());
        }

        // Deserialize players
        try
        {
            cereal::JSONInputArchive archive_players(file_players);
            archive_players(cereal::make_nvp("players", loadedPlayers));
        }
        catch (const cereal::Exception &e)
        {
            throw std::runtime_error(std::string("Error reading players.json: ") + e.what());
        }

        // Deserialize shops
        try
        {
            cereal::JSONInputArchive archive_shops(file_shops);
            archive_shops(cereal::make_nvp("shops", loadedShops));
        }
        catch (const cereal::Exception &e)
        {
            throw std::runtime_error(std::string("Error reading shops.json: ") + e.what());
        }

        // Assign data to player
        if (loadedPlayers.find("player1") != loadedPlayers.end())
        {
            player.inventory.coins = loadedPlayers.at("player1").coins;
            player.stats = loadedPlayers.at("player1").stats;
            // Assign items to the player's inventory based on players data
            for (const auto &itemPair : loadedPlayers.at("player1").items)
            {
                std::string itemName = itemPair.first;
                int itemValue = itemPair.second;

                // Ensure item exists in loaded items before accessing
                if (loadedItems.find(itemName) != loadedItems.end())
                {
                    Item itemToAdd = loadedItems.at(itemName);
                    itemToAdd.value = itemValue;
                    player.inventory.items.insert({itemName, itemToAdd});
                }
            }
        }

        // Assign data to shop
        if (loadedShops.find("basic_shop") != loadedShops.end())
        {
            shop.coins = -1;
            for (const auto &itemPair : loadedShops.at("basic_shop").items)
            {
                std::string itemName = itemPair.first;
                int itemValue = itemPair.second;

                // Ensure item exists in loaded items before accessing
                if (loadedItems.find(itemName) != loadedItems.end())
                {
                    Item itemToAdd = loadedItems.at(itemName);
                    itemToAdd.value = itemValue;
                    shop.items.insert({itemName, itemToAdd});
                }
            }
        }

        items = loadedItems;
    }
};