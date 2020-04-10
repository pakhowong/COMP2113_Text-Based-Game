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
- Treasures are scattered across the dungeon and are marked by "T". Walk near to collect them for bonus points.
- Monsters are randomly scattered across the dungeon and they will be roaming freely. Avoid them or fight them depending on your choice.  
- If you're thinking of fighting off the monsters, collect the weapons along your path. They are scattered around and are marked "W". Walk near to collect them. 
- When you encounter a monster (represented by "m"), you will be directed to a "battle stage" where you will fight the monster using "Paper-Scissors-Stone" mechanism (represented by "1", "2" and "3" respectively). The monster will be defeated and disappear if you beat them, and you will return back to the spot they've took off. 
- A final boss (represented by "B") is located right before the the goal and will be waiting for you. Unlike other monsters you could choose to avoid, you will have to defeat this one in order to reach the goal and win the game.
- If you are defeated by the monsters, unfortunately, you lose.
- You can save the current progress of the game by pressing "S" or load any saved progress by pressing "L" on your keyboard.

### Technical Features and Functions
(For each function, comments on “what it does”, “what the inputs are” and “what the outputs are” are needed)

1. Generation of random game sets or events
- "Monsters" (represented by "m"), "treasures" (represented by "T"), and "weapons" (represented by "W") will be randomly generated across the map
- During the "battle stage" where the player fights against the monsters using "Paper-Scissors-Stone" mechanism, the choice of the monster will be randomised
- The map (which covers the obstacles represented by "X" and the safe paths represented by "0" that the player will walk on) will be randomly generated. A function will be created to evaluate whether the map generated is valid or not by checking whether there is at least one possible path for all game elements (including the player, monsters and treasures) to move from the starting point to the goal.

2. Data structures for storing game status
- A struct of integers will be created to store the user information, such as "location" of both the player and monsters in terms of X-axis and Y-axis, "treasures" the player has collected so far, "weapons" the player possesses.

3. Dynamic memory management
- The map will be stored in a dynamic 2-D array as the player will be allowed to determine the size of the map (i.e. the width and height).
- As "monsters" will be disappered after they are defeated by the player, details of the "monsters" will be stored using a linked list, and the data for individual monster will be removed from the linked list when they are defeated.

4. File input/outout (e.g. for loading/saving game status)
- The player can save their current progress of the game anytime by pressing "S" and load any saved progress by pressing "L" on their keyboard.
- Upon saving, game details including (1) the player's current location (X-axis and Y-axis); (2) the exisiting monsters' current location; (3) the existing treasures' location; (4) size of the map (width and height) and (5) the entire dynamic 2-D array storing the map (including the location of obstacles and walkable paths), will be output to a ".txt" file under the same directory as the program.
- All the above saved game details will be loaded back to their respective linked list or arrays when the player selected a save file (in ".txt" format) to load.

5. Program codes in multiple files 
- 
