# RpgGame
An RPG-like game with a virtual world—all inside your console.
This project uses the Cereal library for JSON serialization.
**Note:** The game is in development, so all ideas and issues are welcome!

## Compiling
### For Linux/Mac 
 1. Make **compile_all.sh** executable: `chmod +x compile_all.sh`
 2. Run the script: `./compile_all.sh`

### For Windows
 1. Open the Command Prompt.
 2. Run the script: `compile_all.bat`

## Start
Start the game by running `./setup`, which creates the **data.json** file where all information is stored.

## Quick Tour
 - **./inventory** - Displays your inventory.
 - **./shop** - Shows the shop and available products to buy.
 - **./buy_from_shop** and **./sell_to_shop** - Manage purchasing and selling items.
 - **./loot_chest** - Simulates opening a loot chest (currently for testing, may be removed in the future).
