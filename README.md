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

### Controls
- Player movement: W" (Up), "A" (Left), "S" (Down) and "D" (Right)
- Battle (Paper-Scissors-Stone): "1" (Paper), "2" (Scissors) and "3" (Stone)
- Save progress: "S"
- Load previously saved progress: "L"
- Players will be asked to input the map size (width and height) as well as their names when the game starts

### Representations
- "P": The playable character
- "X": Obstacles
- "0": Walkable zones (i.e. the roads that you will be walking on to get to the "goal")
- "B": The final boss
- "m": Monsters
- "T": Treasures
- "W": Weapons

### Basic Game Rules
- Control the movement of the character using "W" (Up), "A" (Left), "S" (Down) and "D" (Right).
- You can only walk along safe paths represented by "0" and you cannot walk through obstacles and walls represented by "X".
- Treasures are scattered across the dungeon and are marked by "T". Walk near to collect them for bonus scores (1 point for each treasure).
- Monsters are randomly scattered across the dungeon and they will be roaming freely. Avoid them or fight them depending on your choice. Upon defeating a monster, you will collect 2 points.
- If you're thinking of fighting off the monsters, collect the weapons along your path. They are scattered around and are marked "W". Walk near to collect them.
  - You will have an initial attack point of 1, which essentially reduce the monsters' "hit point" ("HP") by 1 upon winning a round of "Paper-Scissors-Stone". All monsters will have a HP of 5.
  - At least one weapon is required to defeat the final boss.
- When you encounter a monster (represented by "m"), you will be directed to a "battle stage" where you will fight the monster using "Paper-Scissors-Stone" mechanism (represented by "1", "2" and "3" respectively). The monster will be defeated and disappear if you beat them, and you will return back to the spot they've took off.
  - You will have an initial HP of 10. If you lose a round of "Paper-Scissors-Stone", the monster will be able to launch a "fireball" attack which essentially reduce your HP by 1. If you HP is reduced to 0, unfortunately, you lose.
- A final boss (represented by "B") is located at the "goal" and will be waiting for you. Unlike other monsters you could choose to avoid, you will have to defeat this one in order to win the game. The final boss will have a HP of 10.
- You can save the current progress of the game by pressing "S" or load any saved progress by pressing "L" on your keyboard.

### Technical Features and Functions

**1. Generation of random game sets or events**
- The map (which covers the obstacles represented by "X" and the safe paths represented by "0" that the player will walk on) will be randomly generated.
  - The map-generating function will take 2 variables namely "width" and "height" (both inputted by the player) and then output either "X" or "0" into a dynamic 2-D array using "width" and "height" as the parameters. That is, the function will first generate integers of either "1" or "0". Then, all the "1s" will be replaced by "X" (representing obstacles) in the 2-D array while "0s" will remain unchanged (representing walkable zones).
  - Another boolean function will be employed to check whether the map is valid or not (i.e. whether the player could reach the goal or not). Please refer to the third bullet point for details.
- "Monsters" (represented by "m"), "treasures" (represented by "T"), and "weapons" (represented by "W") will be randomly generated across the map
  - In particular, this function will take in the previously generated dynamic 2-D array storing the map data, as well as 3 user inputted variables indicating the amount of "monsters", "treasures" and "weapons". Then, based on the "width" and "height" of the map, this function will generate 2 numbers (i.e. the X-coordinate and Y-coordinate) randomly for each "monster", "treasure" and "weapon".
  - Another boolean function will be created to check the validity of the coordinates. That is, to check whether the generated coordinates fall on the walkable zones on the map (indicated by "0" in the dynamic 2-D array storing map data). If any of the generated coordinates does not equal to any "0" in the map array, this boolean function will return "false", thereby forcing the game element generation function to produce another set of proper coordinates.
  - Apart from that, a last boolean function will be used for checking whether the game element (monsters, treasures and weapons) could be accessible by the player. Please refer to the third bullet point for details.
- A function will be created to check the player's accessibility of game elements by checking whether there is at least one possible path for all game elements (including the player, monsters, weapons and treasures) to move from the starting point to the goal.
  - This boolean function will take in dynamic 2-D map array, and a set of X and Y coordinates. This boolean function will be called when generating the coordinated of the player, monsters, treasures and weapons by respective functions.
  - It will check whether a "path" could be found linking the coordinate of "goal" (fixed at a particular corner) and the concerned coordinates passed by respective functions (i.e. the coordinates of the player, monsters, treasures and weapons). If a path could not be found, "false" will be returned, and vice versa.
  - By ensuring all generated game elements coud be linked to the "goal", it assures that all game elements are accessible by the player with the "goal" as the central connection point.
- During the "battle stage" where the player fights against the monsters using "Paper-Scissors-Stone" mechanism, the choice of the monster will be randomised.
  - This is a function without taking any input. It will simply generate a random number from 1 to 3 (representing "paper", "scissors" and "stone" respectively).

**2. Data structures for storing game status**
- A structure ("struct") of integers will be created to store the game data, such as "location" of the player, monsters, treasures and weapons in terms of X-coordinate and Y-coordinate, the current score, and the "weapons" the player possesses.
  - The structure will be a "structure of structures" (i.e. the location of the player, monsters, treasures and weapons are stored in respective structures (in integer form of X and Y coordinates)).
- Whenever the player decides to quit, the data within the structure is exported into a text file (.txt) and will be labelled using the player's name (stored in a string variable inputted by the player when the game launches). 
  - Please refer to section "4. File input and output" for more details concerning the saving and loading of the game progress.  

**3. Dynamic memory management**
- The map will be stored in a dynamic 2-D array as the player will be allowed to determine the size of the map (i.e. the width and height).
  - When the game launches, the player will be prompted to input 2 integer variables of "width" and "height" of the map. This function will then use the "width" and "height" as the parameters to initialise the dynamic 2-D array by "X" and "0", representing the obstacles and walkable zones respectively, using a random number generator. For details, please refer to the first bullet point in the section "1. Generation of random game sets or events".
- As "monsters" will be disappered after they are defeated by the player while "treasures" and "weapons" will be disappered after they are "collected" by the player by moving near them, details of the game elements including "monsters", "treasures" and "weapons" will be stored using a linked list, and the data for individual monster will be removed from the linked list when they are defeated.
  - As mentioned in the section "2. Data structures for storing game status", game elements such as the "monsters", "treasures" and "weapons" are in fact a set of integer variables (X and Y coordinates) grouped under a structure ("struct"). Therefore, the linked lists will be arrays of structure of integers plus the next linked list element.
  - The various elements in the linked lists will be initialised when the game launches using respective random number generation functions. Please refer to the section "1. Generation of random game sets or events".
- The linked lists will be properly deleted when the game ends in order to free up computer resources.

**4. File input and outout (e.g. for loading and saving game status)**
- The player can save their current progress of the game anytime by pressing "S" and load any saved progress by pressing "L" on their keyboard.
- Upon saving, game details including (1) the player's current location (X-coordinate and Y-coordinate); (2) the exisiting monsters' current location; (3) the existing treasures' location; (4) size of the map (width and height); (5) the entire dynamic 2-D array storing the map (including the location of obstacles and walkable zones) and (6) the current score of the player, will be output to a ".txt" file under the same directory as the program.
  - Please refer to the section "2. Data structures for storing game status" for the details concerning the storing of the above game details (all X and Y coordinates will be stored using structures while the score will be stored in an integer variable).
  - The player will be prompted to input a name when the game starts, which will be stored in a string variable and used as the file name for the save log (in ".txt" format).
- All the above saved game details will be loaded back to their respective linked list or arrays when the player selected a save file (in ".txt" format) to load.
  - When the player restarts the game and enters one's name, a function will check if a file under that name exists in a specified directory. If a file exists, the game will present an option asking if one wants to reload the previous progress.
  - Upon the answer yes, the game reloads the progress. When loading, the members within the structure will be read in order. If no, initialisation begins and the members within the structure will reset to the default value.

**5. Program codes in multiple files**
- Upon the start of the game, ask the player to enter the name. The name entered will be used to name of the save log which is used to store and load the game status. 
  - The save log (in ".txt" format) will contain all data from a structure used for storing in-game progress. The structure has members of integers that can save information of the player: (1) the entire dynamic 2-D array storing the map (including the location of obstacles and walkable paths), (2) the latest location of the player in a coordinate, (3) the latest location of existing monsters in a coordinate, (4) the location of the treasures that were randomly generated on the first time of the play, (5) the location of the weapons that were randomly generated on the first time of the play, (6) the number of treasures the player has collected, (7) the number of weapons the player has collected, (8) the number of monsters the player has defeated, (9) total score.   
- All game elements will be created using structures or classes. It contains the following information: (1) current location (2 integers storing the X and Y coordinates); (2) the current HP level and (3) the number of attacks (i.e. "fireball") on the player.
- Command is created using the class type. A base class is created to represent a triggerable game command; subclass is created for each actions: 4 direction keys and 3 other keys for attack and collect. Another class "InputHandler" is created and a pointer is stored to each command, and thus delegating each key to its role. 
- The game loops are created for serving several purposes: 
  - to process user input, updates the game state, and renders the game by generating an image from 2D array. But the loop does not wait for the user input. Instead, even without the input, the loop continuously runs to generate the background or animation effects if needed.  
  - to run the game in a consistent speed by tracking the passage of time.
