@echo off

:: Compile each file
g++ -std=c++11 setup.cpp -o setup -I. || goto :error
g++ -std=c++11 shop.cpp -o shop -I. || goto :error
g++ -std=c++11 buy_from_shop.cpp -o buy_from_shop -I. || goto :error
g++ -std=c++11 sell_to_shop.cpp -o sell_to_shop -I. || goto :error
g++ -std=c++11 inventory.cpp -o inventory -I. || goto :error
g++ -std=c++11 loot_chest.cpp -o loot_chest -I. || goto :error

echo All files compiled successfully.
goto :eof

:error
echo Error compiling one or more files.
