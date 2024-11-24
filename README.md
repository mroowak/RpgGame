# Adventure Game

Welcome to **Adventure Game**, a simple game where you interact with the world by running commands like `inventory`, `shop`, and others. This game is currently under development and serves as a testbed for various features.

---

## How to Play
To perform actions, execute the corresponding command file:
- **Inventory**: Check your inventory by running `inventory`.
- **Shop**: Interact with the shop by running `shop`.
- **Loot Chest**: Temporarily available for testing, run `loot_chest` to open a chest.

Each executable represents an action you can perform in the game. 

---

## Compilation Instructions
The game includes scripts for compiling all source files into executables. Depending on your operating system, use the appropriate script:
- **Linux/Mac**: Run `compile_all.sh`.
- **Windows**: Run `compile_all.bat`.

These scripts will generate the executables in the `bin` directory.

---

## Configuration
You can customize the starting position of the player by editing the JSON configuration files in the `config` folder. These files control various initial game parameters.

---

## About
- The game is **under active development**, and features are subject to change.
- It uses the [Cereal](https://uscilab.github.io/cereal/) library for serialization.

---

## Contributing
Contributions are welcome! Feel free to fork the repository, make changes, and submit a pull request.

---

## Notes
- **Temporary Testing**: The `loot_chest` executable is available for temporary testing purposes and may be removed or replaced in future updates.
- Expect bugs and incomplete features as the game evolves.

---

## License
This project is open-source, but if you want to use the code please mention me.

Enjoy the adventure!
