@echo off
:: Set the output directory
set "output_dir=bin"
if not exist "%output_dir%" (
    mkdir "%output_dir%"
)

set "include_path=.;./cereal"

g++ -std=c++11 -I"%include_path%" -o "%output_dir%\setup.exe" src\setup.cpp
if errorlevel 1 goto :error

g++ -std=c++11 -I"%include_path%" -o "%output_dir%\inventory.exe" src\inventory.cpp
if errorlevel 1 goto :error

g++ -std=c++11 -I"%include_path%" -o "%output_dir%\shop.exe" src\shop.cpp
if errorlevel 1 goto :error

g++ -std=c++11 -I"%include_path%" -o "%output_dir%\buy_from_shop.exe" src\buy_from_shop.cpp
if errorlevel 1 goto :error

g++ -std=c++11 -I"%include_path%" -o "%output_dir%\sell_to_shop.exe" src\sell_to_shop.cpp
if errorlevel 1 goto :error

g++ -std=c++11 -I"%include_path%" -o "%output_dir%\loot_chest.exe" src\loot_chest.cpp
if errorlevel 1 goto :error

echo All compilations successful! Run the programs from "%output_dir%\[executable_name].exe"
echo If you are starting a new game start with running "%output_dir%\setup.exe" to initialize game.
goto :eof

:error
echo Compilation failed. Check the output above for details.
exit /b 1
