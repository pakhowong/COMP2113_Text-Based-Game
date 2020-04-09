# Proposal of the Text-based Game
COMP2113 group project (a text-based game) written in C++.

Group Number: 97

### Team Members
- Gahyun Lee (3035555834)
- Wong Pak Ho (3035482623)

### Game Introduction
Name of the game: #GAME_NAME#   - maybe come up with the name of our game? 

Genre: Labyrinth Role-playing Game

In #GAME_NAME#, you play as a legendary adventurer stuck inside a dungeon during one of your exploration quests. In order to return home safely with the treasure you discovered in the dungeon, you must find a way out while fending off against monsters and their mysterious boss lurking around.

### Basic Game Rules
- Control the movement of the character using "W" (Up), "A" (Left), "S" (Down) and "D" (Right).
- You can only walk along safe paths represented by "0" and you cannot walk through obstacles and walls represented by "X".
- Treasures are scattered across the dugeon and are marked by "T". Walk near to collect them for bonus points.
- Monsters are randomly scattered across the dungeon and they will be roaming freely. Avoid them or fight them depending on your choice.
- When you encountered a monster, you will be directed to a "battle stage" where you will fight the monster using "Paper-Scissors-Stone" mechanism (represented by "1", "2" and "3" respectively). The monster will be defeated and disappear if you beat them, and you will return back to the original stage
- After avoiding or defeating all monsters, a final boss will be located right before the the goal. Similar to other monsters, you will have to defeat it before reaching the goal and win the game.
- If you are defeated by the monsters unfortunately, you lose.
- You can save the current progress of the game by pressing "S" or load any saved progress by pressing "L" on your keyboard.

### Technical Features and Functions
(For each function, comments on “what it does”, “what the inputs are” and “what the outputs are” are needed)

1. Generation of random game sets or events 
2. Data structures for storing game status 
3. Dynamic memory management
4. File input/outout (e.g. for loading/saving game status)
5. Program codes in multiple files 
