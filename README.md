# COMP2113 Text-based Game
COMP2113 group project (a text-based game) written in C++.

Group Number: 97

### Team Members
- Gahyun Lee (3035555834)
- Wong Pak Ho (3035482623)

### Game Introduction
Name of the game: Pop-It Pat 

Genre: Labyrinth Role-playing Game

In *Pop-It Pat*, you play as a legendary adventurer stuck inside a dungeon during one of your exploration quests. In order to return home safely with the treasure you discovered in the dungeon, you must find a way out while fending off against monsters and their mysterious boss lurking around.

### Basic Controls
- Player movement: "W" (Up), "A" (Left), "S" (Down) and "D" (Right)
- Battle (Paper-Scissors-Stone): "1" (Paper), "2" (Scissors) and "3" (Stone)
- Quit game and save progress: "Q"
- Players will be asked to input the game difficulty (i.e. map size) and whether or not to load previously saved progress when the game starts

### Representations
- "P": The playable character
- "x": Obstacles
- ".": Walkable zones (i.e. the roads that you will be walking on to get to the "goal")
- "B": The final boss, which stayed at the goal
- "m": Monsters
- "T": Treasures
- "W": Weapons

### Basic Game Rules
- Control the movement of the character using "W" (Up), "A" (Left), "S" (Down) and "D" (Right).
- You can only walk along safe paths represented by "." and you cannot walk through obstacles and walls represented by "x".
- Treasures are scattered across the dungeon and are marked by "T". Walk near to collect them for bonus scores (1 point for each treasure).
- Monsters ("m") are randomly scattered across the dungeon and they will be roaming freely. Avoid them or fight them depending on your choice. Upon defeating a monster, you will collect 2 points.
- If you're thinking of fighting off the monsters, collect the weapons along your path. They are scattered around and are marked "W". Walk near to collect them.
  - You will have an initial attack point of 1, which essentially reduce the monsters' "hit point" ("HP") by 1 upon winning a round of "Paper-Scissors-Stone". All monsters will have a HP of 5.
- When you encounter a monster (represented by "m"), you will be directed to a "battle stage" where you will fight the monster using "Paper-Scissors-Stone" mechanism (represented by "1", "2" and "3" respectively). The monster will be defeated and disappear if you beat them, and you will return back to the spot where you took off.
  - You will have an initial HP of 10. If you lose a round of "Paper-Scissors-Stone", the monster will be able to launch a "fireball" attack which essentially reduce your HP by 1. If you HP is reduced to 0, unfortunately, you lose.
- A final boss (represented by "B") is located at the "goal" and will be waiting for you. Unlike other monsters you could choose to avoid, you will have to defeat this one in order to win the game. The final boss will have a HP of 10.
- You can quit and save the current progress of the game by pressing "Q" anytime except during the battle stage.
- You can load the previously saved progress by choosing "2: Load" when the game first starts.

### Technical Features and Functions

**1. Generation of random game sets or events**
- The map (which includes the obstacles represented by "x" and the safe paths represented by "." that the player will walk on) will be randomly generated.
  - The map-generating function will take 2 integers namely "width" and "height" (both determined by the user-inputted "game difficulty", in which the map will be larger if the difficulty is harder) and then output either "-1" or "0" into a dynamic 2-D vector using "width" and "height" as the parameters.
    - That is, the function will first generate integers from 0 to 4, with 0 represents the obstacles "x" and 1 to 4 represent the walkable zones ".".
    - The numerical map with integers 0 to 4 will be converted to the actual map (displayed using characters "x" and ".") afterwards.
  - Another boolean function will be employed to check whether the map is valid or not (i.e. whether the player could reach the goal or not). Please refer to the third bullet point for details.
- "Monsters" (represented by "m"), "treasures" (represented by "T"), and "weapons" (represented by "W") will be randomly generated across the map
  - In particular, this function will take in the previously generated dynamic 2-D vector storing the map data.
  - Then, based on the "width" and "height" of the map, this function will generate 2 numbers (i.e. the x-coordinate and y-coordinate) randomly for each "monster", "treasure" and "weapon".
  - Another boolean function will be created to check the validity of the coordinates. That is, to check whether the generated coordinates fall on the walkable zones on the map (indicated by "." in the dynamic 2-D vector storing map data). If any of the generated coordinates does not equal to "." in the map vector, this boolean function will return "false", thereby forcing the game element generation function to produce another set of proper coordinates.
- All "monsters" ("m") in the game are allowed to roam freely. That is, they can move around the map on all "walkable zones" (represented by ".") just like the player do. Their movement will be random and they can move in all four directions (i.e. up, down, left and right). In particular, it will be generated with a random number generator of 1 to 4, each representing a different direction. A boolean function will be used to check whether the intended direction has any obstacles ("x") or not. If yes, the monster cannot walk there, and vice versa.
- A function will be created to check the player's accessibility to the goal (i.e. the final boss) by checking whether there is at least one possible path for the player to move from the starting point to the goal.
  - This boolean function will take in dynamic 2-D map vector, and a set of x- and y-coordinates. This boolean function will be called when generating the coordinated of the player.
- During the "battle stage" where the player fights against the monsters using "Paper-Scissors-Stone" mechanism, the choice of the monster will be randomised.
  - This is a function without taking any input. It will simply generate a random number from 1 to 3 (representing "paper", "scissors" and "stone" respectively).

**2. Data structures for storing game status**
- Two structures ("struct") will be created to group the game data, such as "location", HP of the player and monsters, as well as other game progress such as the current score, the "weapons" the player possesses, etc.
  - One structure for storing the player-related data and another structure for storing the enemy-related data.
- The game map stored in the dynamic 2-D vector will be stored outside of the two structures as it is neither player-related nor enemy-related. This is to better categorise the game elements.
- Whenever the player decides to quit, the data within the structure is exported into a text file ("savelog.txt").
  - Please refer to section "4. File input and output" for more details concerning the saving and loading of the game progress.  

**3. Dynamic memory management**
- The map will be stored in a dynamic 2-D vector as the player will be allowed to determine the size of the map (i.e. the width and height).
  - The dynamic 2-D vector is necessary in this game because the player is allowed to choose different size of the game map.
    - Even though the dynamic 2-D vector was initialised using the constant "maximum width" and "maximum height", which is more than enough to store the map, it is a waste of computing resources as most of the elements in the 2-D vector is unused but reserved.
    - Furthermore, as the player can choose to load the previously saved game when the game starts, this makes the "map-generation" function useless as the game map is loaded into the game. Therefore, the dynamic 2-D vector will be useless as the "map-generation" function does not need to be called. In that case, allocating an empty 2-D array with the size of the game map is a waste of computing resources. As such, a dynamic 2-D vector is needed, in which the program can "clear" and "destroy" all unused but allocated spaces in order to free up the computing resources.
  - When the game launches, the player will be prompted to choose the level of difficulties of the game (an integer). It will be used to determine the variable (not constant) map size (height and width), the more difficult the game is, the larger the size of the game map is. This function will then use the "width" and "height" as the parameters to initialise the dynamic 2-D vector with "x" and ".", representing the obstacles and walkable zones respectively, using a random number generator. For details, please refer to the first bullet point in the section "1. Generation of random game sets or events".

**4. File input and outout (e.g. for loading and saving game status)**
- The player can save their current progress of the game anytime by pressing "Q". Upon pressing 'Q', the user can quit the game and then store the game progress into a text file called ("savelog.txt").
- The player can choose to load the previously saved game file at the start of the game or start a new game completely.
  - However, if there is no saved game before, the player cannot load any game file as it could disrupt the whole program.
- Upon saving, game details including (1) the player's current location (in x-coordinate and y-coordinate); (2) the exisiting monsters' current location; (3) the existing treasures' location; (4) the game difficulty (which is a single integer representing a lot of game elements including the size of the map, i.e. width and height, and the number of enemies, etc.); (5) the entire dynamic 2-D vector storing the map (including the location of obstacles and walkable zones) and (6) the current score of the player (i.e. the number of defeated monsters, as well as the number of weapon and treasure collected), will be output to a ".txt" file under the same directory as the program.
  - Please refer to the section "2. Data structures for storing game status" for the details concerning the storing of the above game details (in short, all the game elements will be grouped into 3 categories, namely (1) player-related data, (2) enemy-related data and (3) map, and will be stored separately in 2 structures and a vector. All of them will be outputted to the text file "savelog.txt").
- All the above saved game details will be loaded back to their respective variables when the player load the save file (in ".txt" format).
  - When the player restarts the game, the player will always be prompted to choose between starting a new game or load a previous game.
  - Upon choosing to load the previous game, the game reloads the progress. When loading, the members within the structure will be read in order. If no, initialisation begins and the members within the structure will reset to the default value.

**5. Program codes in multiple files**
- battle.cpp : a code with functions related to the battle. The select_difficulty function lets the player chooses the difficulty of the battle. The battle function sets up a basic information regarding the battle background starting from asking player to choose an attack mode to guiding player to the next round upon successful ending of the previous round. 
- commandMovement.cpp : a code with functions related to the basic commands of players and enemies. The enemies_movement function sets up the movement of enemies using random generator and manages the four movements which are move up, left, down, and right. This function also enters players into a battle stage when collided with the enemy during the play. The player_movement function sets up the movement of players using alphabet key. The alphabet 'w', 'a', 's', 'd', 'q' corresponds to move up, left, down, right, and quit respectively. This function also enters players into a battle stage when collided with the enemy during the play. 
- enemy_items.cpp : a code with functions related to generating enemies, items, and weapons for the game. The generate_enemies function generates enemies using random generator; the generate_game_items function also generates game items using random generator. The attack_choice function lets users to choose the attack using paper, scissors, stone algorithm. The destroy_enemy function moves the enemies out of the map so they will stop any further movement, and thus destroys the enemy.  
- gameover_victory.cpp : a code with functions for gameover and victory. When the player fails during one's quest, the gameover function prints out "GAMEOVER" on the screen. On the other hand, upon successful completion of one's journey, the victory function prints out "VICTORY" on the screen, along with the number of treasures collected and enemies killed along the way. At last, the total score is also printed out. 
- map.cpp : a code with functions for map. The generate_map function generates map by resizing vector, using random genreator, and filling the map with either 1 or 0. To guarantee that the randomly generated map is a valid map for the game, the isMapValid function is used for a check. For a non-valid map, there will be no path to the goal; if a path could not be found after exhausting all efforts, the function will return "No". 
- save_load_start_refresh.cpp : a code with functions for save, load, start, and refresh. The startgame function displays the start screen of the game which prints out "Welcome!" and asks if the player is new to the game or not. The save function saves the game status of the player as one presses the alphabet key 'q'. The load function loads the game status of the player such as the HP, treasure, weapon, position, and number of kills. The refresh function clears everything on the screen.  
- stages.cpp : a code with functions for stages. The generate_stage function generates stage by resizing vector and representing the game objects in characters instead of integers. Several functions are dedicated in printing out ASCII art codes for our player and monster. For example, showbattlestage function which displays the player and monster along with menus for attack mode, enemy HP, and the player's HP. Showbossbattlestage function also displays the boss monster using ASCII art and shows the menus for attack mode, boss enemy HP, and the player's HP. The boss_stage function here guides the player that the stage is a boss stage and creates a little pause break for the player before one enters the final stage. 

**6. Non-standard C/C++ libraries**
- No non-standard C/C++ libraries are included in this game. All libraries used are standard C/C++ libraries.

**7. Compilation and execution instructions**
- The game first starts with the "welcoming page" where it will allow the user to choose whether to start a new game or load previously saved game progress.
  - By inputting "1", the player can start a new game and by inputting "2", the player can load previous progress.
    - However, if not progress has been saved previously, the player cannot choose the option of "2. Load game" or else it may lead to unexpected errors.
    - If the player choose to load previous game progress, the player will be directed to the game stage and he or she can continue playing the saved game immediately without any additional input.
- Then, if the player choose to start a new game, the program will ask him or her to choose the level of difficulties (i.e. 1, 2 or 3). Level 1 is the easiest while Level 3 is the hardest. The difference between the levels are the size of the map and the number of enemies. The harder the level is, the larger the map is and more enemies will appear as well.
- After choosing the level, the player can start playing the game. He or she can control the character (represented by "P") using "W", "A", "S" and "D" (preferably in lowercase characters). All players will start at the top left corner and shall move to the bottom right corner (i.e. the goal).
  - In order to make the control more user-friendly, the input will be read by the program in "raw" mode instead of "cooked" mode. That is, the player does not have to click "enter" button everytime.
  - The game (i.e. the screen) will be refreshed everytime the user input a direction (i.e. "W", "A", "S" or "D") so the player can appear to move seamlessly.
  - The player can only move on ".", "T" and "W". "x" are obstacles and "#" are the boundaries that the player cannot cross.
- The player can collect treasures (represented by "T") and weapons (represented by "W") on the way to the last boss (marked by "B").
  - For each treasure, it increases the player's score by 1; and for each weapon, it increases the player's attack by 1 (the player will have an initial attack of 1).
- When the player encountered any monsters ("m") or reached the final boss ("B"), it will triggers the "battle stage". The battle will be in the form of "paper-scissors-stone". The user shall input an integer of 1, 2 or 3, each representing "paper", "scissors" and "stone" respectively. The enemy's choice will be randomly generated and displayed on the screen. The battle result will show whether the user win, lost or draw. For each victory, the enemy's HP will be decreased by the player's attack point (i.e. 1 + number of weapons collected). However, if the player lost the round, the player's HP will be decreased by 1. If the HP is decreased to 0, the game is over and the player lost.
  - Once the player defeated the enemy, he or she will be directed back to the main game. Before that, the player shall randomly press any key (preferably characters) to continue the game.
  - Before entering the battle stage with the boss, the program will ask the user to press any random key (preferably characters) to continue.
  - By defeating the final boss, the player will win the game and the number of collected treasures and the final score will be shown and the program ends.

**8. Sample input and output file**
- Please refer to the "savelog.txt" in this repository for the sample input and output file. Both input and output files are in similar format, which stores the game progress for the player. The player can choose to load the saved game progress when the game starts. The meaning of each data in the text file are as follows:
  - The player-related data:
    - The first integer is the game difficulty, it is a single integer that is used to represent many different variables. For instance, it determines the game map size (2 integer variables of height and width) and the interger variable of the number of enemies.
    - The second integer is the player's remaining HP (initially 10).
    - The third and fourth integers are the number of treasures and weapons that the player collected so far.
    - The fifth and sixth integers are the player's y- and x-coordinates.
    - The seventh integer is the number of enemies that the player killed, it is use to determine the final score.
  - The entire game map 
  - The enemy-related data:
    - For every 3 integers, they represent 1 enemy.
    - In each set of 3 integers, the first one is the enemy's HP, the second and third ones are the enemy's y- and x-coordinates.
