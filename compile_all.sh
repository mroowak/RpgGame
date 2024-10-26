#!/bin/bash

# Compile each file
g++ -std=c++11 setup.cpp -o setup -I. &&
g++ -std=c++11 shop.cpp -o shop -I. &&
g++ -std=c++11 buy_from_shop.cpp -o buy_from_shop -I. &&
g++ -std=c++11 sell_to_shop.cpp -o sell_to_shop -I. &&
g++ -std=c++11 inventory.cpp -o inventory -I. &&
g++ -std=c++11 loot_chest.cpp -o loot_chest -I.

# Check if all files compiled successfully
if [ $? -eq 0 ]; then
  echo "All files compiled successfully."
else
  echo "Error compiling one or more files."
fi
