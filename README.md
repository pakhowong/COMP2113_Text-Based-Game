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
- A struct of integers will be created to store the user information, such as "location" of both the player and monsters in terms of X-axis and Y-axis, "treasures" the player has collected so far, "weapons" the player possesses. The structure will be labeled as the name the player enters at the beginning of the game. 
- Whenever the player decides to quit, the data within the structure is stored into another file and will be labeled using the same name as the structure. When the player reloads and enters one's name, check to see if the file under that name exists. If the file exists, the game present an option asking if one wants to reload the previous progress. 
- Upon the answer yes, the game reloads the progress. When loading, the members within the structure will be read in order. If no, initialization begins and the members within the structure re-sets to the default value.  

3. Dynamic memory management
- The map will be stored in a dynamic 2-D array as the player will be allowed to determine the size of the map (i.e. the width and height).
- As "monsters" will be disappered after they are defeated by the player, details of the "monsters" will be stored using a linked list, and the data for individual monster will be removed from the linked list when they are defeated.

4. File input/outout (e.g. for loading/saving game status)
- The player can save their current progress of the game anytime by pressing "S" and load any saved progress by pressing "L" on their keyboard.
- Upon saving, game details including (1) the player's current location (X-axis and Y-axis); (2) the exisiting monsters' current location; (3) the existing treasures' location; (4) size of the map (width and height) and (5) the entire dynamic 2-D array storing the map (including the location of obstacles and walkable paths), will be output to a ".txt" file under the same directory as the program.
- All the above saved game details will be loaded back to their respective linked list or arrays when the player selects a save file (in ".txt" format) to load.

5. Program codes in multiple files 
- Upon the start of the game, ask the player to enter the name. The name entered will be used to name of the structure which is used to store and load the game status. 
- The structure has members of integers that can save information of the player: (1) the entire dynamic 2-D array storing the map (including the location of obstacles and walkable paths), (2) the latest location of the player in a coordinate, (3) the latest location of existing monsters in a coordinate, (4) the location of the treasures that were randomly generated on the first time of the play, (5) the location of the weapons that were randomly generated on the first time of the play, (6) the number of treasures the player has collected, (7) the number of weapons the player has collected, (8) the number of monsters the player has defeated, (9) total score. 
- Command is created using the class type. A base class is created to represent a triggerable game command; subclass is created for each actions: 4 direction keys and 3 other keys for attack and collect. Another class "InputHandler" is created and a pointer is stored to each command, and thus delegating each key to its role. 
- Enemies will be created using the class type. It contains the following information: (1) current location, (2) the full HP level, (3) how many HP gets reduced on one attack from the user -- depending and varies on the type of weapon used, (4) the current HP level, (5) total number of fireballs it can spit, (6) the remaining number of fireballs left. 
- 
