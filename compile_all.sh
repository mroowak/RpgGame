#!/bin/bash
# Make sure Cereal is accessible in the include path and set the output directory
output_dir="bin"
mkdir -p $output_dir

# Compile each source file into a separate executable
g++ -std=c++11 -I. -I./cereal -o $output_dir/setup src/setup.cpp
g++ -std=c++11 -I. -I./cereal -o $output_dir/inventory src/inventory.cpp
g++ -std=c++11 -I. -I./cereal -o $output_dir/shop src/shop.cpp
g++ -std=c++11 -I. -I./cereal -o $output_dir/buy_from_shop src/buy_from_shop.cpp
g++ -std=c++11 -I. -I./cereal -o $output_dir/sell_to_shop src/sell_to_shop.cpp
g++ -std=c++11 -I. -I./cereal -o $output_dir/loot_chest src/loot_chest.cpp

# Check if compilation was successful for each executable
if [ $? -eq 0 ]; then
    echo "All compilations successful! Run the programs with ./$output_dir/[executable_name]"
    echo "If you are starting a new game start with running ./$output_dir/setup to initialize game."
else
    echo "Compilation failed."
fi
