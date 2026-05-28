# Hero vs Monsters: Battle Simulator

An interactive, text-based RPG battle simulator written in **C++** utilizing **Object-Oriented Programming (OOP)** principles. The game features an endless dungeon-crawler experience where a hero fights randomized monsters, manages survival through tactical choices, and faces scaling boss fights.

## Key Features
* **Object-Oriented Architecture:** Clean separation of concerns with `Hero`, `Monster`, and `weapon` classes.
* **Advanced Combat Ruleset:** Dynamic damage calculations including accuracy checks (Armor Class vs Hit Roll) and damage reduction based on custom defense stats.
* **Special Skills System:** * *Hero Skills:* Power Strike, Double Slash, Piercing Thrust (ignores armor), and Critical Blow.
  * *Monster AI:* Smart decision-making flow (70% Simple Attack / 30% Special Skills like Heavy Smash or Poison Fang).
* **Epic Boss Events:** An scaling boss fight (`🚨 EPIC BOSS: Dragon 🐉`) triggers every 5 kills with enhanced stats and custom weaponry.
* **Quality of Life Functions:** Complete menu input validation (prevents crashes from invalid choices), custom healing mechanic, and a seamless *Play Again* replay loop.

## 🛠️ Technologies Used
* **Language:** C++ (ISO C++11 or higher)
* **IDE:** Dev-C++ / Code::Blocks
* **Libraries:** `<iostream>`, `<string>`, `<cstdlib>`, `<ctime>`, `<windows.h>`

## How to Play
1. Compile and run the `main.cpp` file using any C++ compiler.
2. Enter your Hero's name and receive a randomized starter weapon.
3. Choose your action each turn: Simple Attack, Special Skill, or Heal.
4. Defeat as many monsters as you can before your HP hits 0!
