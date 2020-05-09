#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// ********** Constants **********

const int Max_map_height = 30, Max_map_width = 60;
const int Max_enemies = 9;

// Game elements
vector < vector < int > > map (Max_map_height, vector < int > (Max_map_width, 0));  // Initialise the 2-D array of map with the maximum map size allowed
vector < vector < char > > stage (Max_map_height, vector < char > (Max_map_width, 0));



// ********** Gloabl variables **********

int NumOfEnemies;
bool isGameover = false;
bool isBossStage = false; 

struct players {
    int y = 0, x = 0;
    int treasure = 0, weapon = 0;
    int HP = 10;
    int kills = 0;
} player;

struct enemies {
    int health = 5; // Enemies' HP
    int y, x;   // Enemies' y- and x-coordinates
} enemy[Max_enemies];



// ********** Function declarations **********

void save(int, int, int);
void refresh();
int select_difficulty();
void generate_map(int, int);
bool isMapValid(int, int);
void generate_enemies(int, int, int);
void generate_game_items(int, int, int);
void generate_stage (int, int);
void showstage(int, int);
void destroy_enemy(int);
string attack_choice(int);
void gameover();
void victory();
void showbattlestage(int);
int battle(int);
void enemies_movement();
void move(int, int, int);
bool isGoal(int, int);
void boss_stage();
void save(int, int, int);
void load(int &difficulty,int &height, int &width);
bool startgame();



// ********** Functions **********

void refresh() {
    // Linux ONLY
    // To clear everything on the screen
    printf("\033c");
}

int select_difficulty() {
    int difficulty = 0, temp = 0;
    // Allow user to choose various difficulties (size of the map)
    system("stty raw");
    cout << "Please choose the levels of difficulty (1, 2 or 3): ";
    cin >> temp;
    if ((temp == 1) || (temp == 2) || (temp == 3)) {
        difficulty = temp;
    }
    while ((difficulty < 1) || (difficulty > 3)) {
        cout << "Please choose the levels of difficulty (1, 2 or 3): ";
        system("stty raw");
        cin >> temp;
        system("stty cooked");
        if ((temp == 1) || (temp == 2) || (temp == 3)) {
            difficulty = temp;
            break;
        }
    }
    system("stty cooked");
    return difficulty;
}

void generate_map(int height, int width) {
    map.clear();
    map.resize(height, vector<int>(width)); // Resize the vector (2-D dynamic map)

    int RNG;
    
    srand(time(0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RNG = rand();
            RNG = RNG % 5;
            //cout << RNG << " ";
            map[i][j] = RNG;  // Fill the map with either 1 or 0
            if (map[i][j] == 0) {
                map[i][j] = -1; // Change all 0 to -1 in order to facilitate the later checking of map vaidity
            }
            else if (map[i][j] != 0) {
                map[i][j] = 0;
            }
        }
    }

    // Set the start and end point
    map[0][0] = 1;
    map[height - 1][width - 1] = -2;
}

bool isMapValid(int height, int width) {
    int temp_map[Max_map_height][Max_map_width];
    
    // Create a copy of the map
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp_map[i][j] = map[i][j];
        }
    }
    
    int steps = 1;
    int w = 0, h = 0;
    bool found = false, valid = false, exhaust = false;

    // Check if the map have "-2" (i.e. the goal) or not
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (temp_map[i][j] == -2) {
                valid = true;
                break;
            }
        }
    }
    // For non-valid map (i.e. without goal), there will be no path to the goal
    if (not valid) {
        return 0;
    }

    while (valid && (not found) && (not exhaust)) {
        // Loop through the map to find the target node
        // i.e. "1" represet the starting point
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (temp_map[i][j] == steps) {
                    h = i;
                    w = j;
                    
                    // Break the loop and return the number of steps if -2 (i.e. goal) is found
                    if (temp_map[h - 1][w] == -2) {
                        // Top
                        found = true;
                        break;
                    }
                    if (temp_map[h + 1][w] == -2) {
                        // Down
                        found = true;
                        break;
                    }
                    if (temp_map[h][w - 1] == -2) {
                        // Left
                        found = true;
                        break;
                    }
                    if (temp_map[h][w + 1] == -2) {
                        // Right
                        found = true;
                        break;
                    }

                    // Filling all neighbouring "0" nodes with (steps + 1)
                    if (temp_map[h - 1][w] == 0) {
                        temp_map[h - 1][w] = steps + 1;
                    }
                    if (temp_map[h + 1][w] == 0) {
                        temp_map[h + 1][w] = steps + 1;
                    }
                    if (temp_map[h][w - 1] == 0) {
                        temp_map[h][w - 1] = steps + 1;
                    }
                    if (temp_map[h][w + 1] == 0) {
                        temp_map[h][w + 1] = steps + 1;
                    }
                }
            }
        }
        steps++;

        // Check if all possibilities have been eliminated
        if (steps > (height * width)) {
            exhaust = true;
        }
    }

    // If a path could not be found after exhausting all efforts, return "No"
    if (exhaust) {
        steps = 0;
    }

    if ((steps - 1) > 0) {
        return true;
    }
    else {
        return false;
    }
}

void generate_enemies(int height, int width, int difficulty) {
    int probability, enemy_counter = 0, RNG;
    bool enemies_are_generated = false;
    switch(difficulty) {
        case 1:
            probability = 50;
            NumOfEnemies = 3;
            break;
        case 2:
            probability = 75;
            NumOfEnemies = 6;
            break;
        case 3:
            probability = 100;
            NumOfEnemies = 9;
            break;
    }
    while (not enemies_are_generated) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                RNG = rand();
                RNG = RNG % probability; // Probability of generating an enemy
                if ((stage[i][j] == '.') && (RNG == 1)) {
                    stage[i][j] = 'm';
                    // Set the enemies' location
                    enemy[enemy_counter].y = i;
                    enemy[enemy_counter].x = j;

                    enemy_counter++;
                    if (enemy_counter == NumOfEnemies) {
                        enemies_are_generated = true;
                        break;
                    }
                }
                if (enemy_counter == NumOfEnemies) {
                    enemies_are_generated = true;
                    break;
                }
            }
            if (enemy_counter == NumOfEnemies) {
               enemies_are_generated = true;
                break;
            }
        }
    }
}

void generate_game_items(int height, int width, int difficulty) {
    // -3 represents "treasures" while -4 represents "weapons" temporarily

    int temp_map[Max_map_height][Max_map_width];
    // Create a copy of the map
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp_map[i][j] = map[i][j];
        }
    }
    
    bool treasure_is_generated = false, weapon_is_generated = false;
    int treasure_counter = 0, weapon_counter = 0;
    int RNG, probability;
    srand(time(0));

    switch(difficulty) {
        case 1:
            probability = 20;
            break;
        case 2:
            probability = 40;
            break;
        case 3:
            probability = 80;
            break;
    }
    
    while ((not treasure_is_generated) && (not weapon_is_generated)) {
        // Generate "treasures" (i.e. -3)
        if (not treasure_is_generated) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    RNG = rand();
                    RNG = RNG % probability; // Probability of generating a treasure
                    if (treasure_counter == 5) {
                        treasure_is_generated = true;
                        break;
                    }
                    if ((temp_map[i][j] == 0) && (RNG == 1)) {
                        temp_map[i][j] = -3;
                        treasure_counter++;
                    }
                }
            }
        }

        // Generate "weapons" (i.e. -4)
        if (not weapon_is_generated) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    RNG = rand();
                    RNG = RNG % probability; // Probability of generating a weapon
                    if (weapon_counter == 5) {
                        weapon_is_generated = true;
                        break;
                    }
                    if ((temp_map[i][j] == 0) && (RNG == 1)) {
                        temp_map[i][j] = -4;
                        weapon_counter++;
                    }
                }
            }
        }

        if (treasure_is_generated && weapon_is_generated) { // Check if enough game items are generated
            // Copy the temporary map back to the "master" map
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    map[i][j] = temp_map[i][j];
                }
            }
        }
    }
}

void generate_stage (int height, int width) {
    stage.clear();
    stage.resize(height, vector<char>(width)); // Resize the vector (2-D dynamic map)

    // Represent the game objects in characters instead of integers
    stage[0][0] = 'P';
    stage[height - 1][width - 1] = 'B';
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == 0) {
                stage[i][j] = '.';
            }
            else if (map[i][j] == -1) {
                stage[i][j] = 'x';
            }
            else if (map[i][j] == -3) {
                stage[i][j] = 'T';
            }
            else if (map[i][j] == -4) {
                stage[i][j] = 'W';
            }
        }
    }
}

void showstage(int height, int width) {
    refresh();

    int score = 0;
    score = ((player.kills * 2) + player.treasure);

    cout << "################" << endl;
    cout << "Treasure:     " << player.treasure << endl;
    cout << "Weapon:       " << player.weapon << endl;
    cout << "Enemy killed: " << player.kills << endl;
    cout << "Your HP:      " << player.HP << endl;
    cout << "Your Score:   " << score << endl;
    cout << "################" << endl << endl;

    for (int i = 0; i < width; i++) {
        cout << "##";   // "#" is the map boundary
    }
    cout << "##" << endl;
    for (int i = 0; i < height; i++) {
        cout << "#";
        for (int j = 0; j < width; j++) {
            cout << stage[i][j] << " ";
        }
        cout << "#" << endl;
    }
    for (int i = 0; i < width; i++) {
        cout << "##";
    }
    cout << "##" << endl;
}

void destroy_enemy(int enemyID) {
    // Move the enemies out of the map (so they wont "move" anymore)
    enemy[enemyID].y = -10;
    enemy[enemyID].x = -10;
    player.kills++;
    // Remove the "m" from the map
    stage[player.y][player.x] = 'P';
}

string attack_choice(int choice) {
    string attack_choice;
    switch(choice) {
        case 1:
            attack_choice = "PAPER";
            break;
        case 2:
            attack_choice = "SCISSORS";
            break;
        case 3:
            attack_choice = "STONE";
            break;
    }
    return attack_choice;
}

void gameover() {
    refresh();
    cout << "GAMEOVER" << endl;
    isGameover = true;
}

void victory() {
    refresh();
    isGameover = true;

    int score = 0;
    score = ((player.kills * 2) + player.treasure);

    cout << "VICTORY" << endl;
    cout << endl << "You have collected " << player.treasure << " treasures ";
    cout << "and killed " << (player.kills + 1) << " enemies!" << endl;
    cout << "Your total score is: " << score << endl;
}

void showbattlestage(int health) {
    refresh();
    //player
    cout << "    _O_    " << endl;    
    cout << "  /     \  " << endl;    
    cout << " |==/=\==| " << endl;   
    cout << " |  O O  | " << endl;    
    cout << "  \  V  /  " << endl;   
    cout << "  /`---'\  " << endl;    
    cout << "  O'_:_`O  " << endl;  
    cout << "   -- --   " << endl; 
    
    //monster 
    cout << "   .-.    " << endl; 
    cout << "  (o o)   " << endl; 
    cout << "  | O \   " << endl; 
    cout << "   \   \  " << endl; 
    cout << "    `~~~' " << endl; 
    
    cout << "###########" << endl;
    cout << "1: Paper   " << endl;
    cout << "2: Scissors" << endl;
    cout << "3: Stone   " << endl;
    cout << "###########" << endl << endl;

    
    cout << "################" << endl;
    cout << " Enemy HP: " << health << endl;
    cout << " Your HP:  " << player.HP << endl;
    cout << "################" << endl << endl;

}

void showbossbattlestage(int health) {
    //boss monster 
    cout << "         (  )   /\   _                 (                                            " << endl;
    cout << "      \ |  (  \ ( \.(               )                      _____                    " << endl;
    cout << "    \  \ \  `  `   ) \             (  ___                 / _   \                   " << endl;
    cour << "   (_`    \+   . x  ( .\            \/   \____-----------/ (o)   \_                 " << endl; 
    cout << "  - .-               \+  ;          (  O                           \____            " << endl;
    cout << "                            )        \_____________  `              \  /            " << endl;
    cout << "  (__                +- .( -'.- <. - _  VVVVVVV VV V\                 \/            " << endl;
    cout << "  (_____            ._._: <_ - <- _  (--  _AAAAAAA__A_/                  |          " << endl;
    cout << "    .    /./.+-  . .- /  +--  - .     \______________//_              \_______      " << endl;
    cout << "    (__ ' /x  / x _/ (                                  \___'          \     /      " << endl;
    cout << "   , x / ( '  . / .  /                                      |           \   /       " << endl;
    cout << "      /  /  _/ /    +                                      /              \/        " << endl;
    cout << "     '  (__/                                             /                  \       " << endl;
}

int battle(int health) {
    refresh();
    int attack = 1 + player.weapon;
    int RNG = 0;
    int input = 0;
    bool battle_end = false;
    
    if (not isBossStage) 
    { 
        showbattlestage(health); 
    }
    else 
    { 
        showbattlestage; 
    } 
    
    while (not battle_end) {
        showbattlestage(health);
        cout << "Choose your attack mode: ";
        cin >> input;
        while ((input > 3) || (input < 1)) {
            cout << "Choose your attack mode: ";
            cin >> input;
            cout << endl;
            if ((input <= 3) && (input >= 1)) {
                break;
            }
        }
        cout << endl << "You chose " << attack_choice(input) << endl;

        RNG = rand();
        RNG = RNG % 3 + 1;  // Random number between 1 to 3
        cout << "Enemy chose " << attack_choice(RNG) << endl;

        if (((input == 1) && (RNG == 3)) || ((input == 3) && (RNG == 2)) || ((input == 2) && (RNG == 1))) {
            // Win
            health -= attack;
            if (health <= 0) {
                battle_end = true;
                break;
            }

            // Reset
            input = 0;
            RNG = 0;

            // Next Round
            cout << endl << "You WIN" << endl;
            cout << endl << "READY FOR NEXT ROUND?" << endl;
            cout << endl << "Press any key to continue" << endl;
            char temp;
            system("stty raw");
            cin >> temp;
            system("stty cooked");
        }
        else if (((input == 1) && (RNG == 2)) || ((input == 2) && (RNG == 3)) || ((input == 3) && (RNG == 1))) {
            // Lose
            player.HP--;
            if (player.HP <= 0) {
                battle_end = true;
                break;
            }

            // Reset
            input = 0;
            RNG = 0;

            // Next Round
            cout << endl << "You LOSE" << endl;
            cout << endl << "READY FOR NEXT ROUND?" << endl;
            cout << endl << "Press any key to continue" << endl;
            char temp;
            system("stty raw");
            cin >> temp;
            system("stty cooked");
        }
        else if (((input == 1) && (RNG == 1)) || ((input == 2) && (RNG == 2)) || ((input == 3) && (RNG == 3))) {
            // Reset
            input = 0;
            RNG = 0;
            
            // Next Round
            cout << endl << "DRAW" << endl;
            cout << endl << "READY FOR NEXT ROUND?" << endl;
            cout << endl << "Press any key to continue" << endl;
            char temp;
            system("stty raw");
            cin >> temp;
            system("stty cooked");
        }
    }

    if (health <= 0) {
        refresh();
        cout << "CONGRATULATION!" << endl;
        cout << endl << "Enemy is defeated" << endl << endl;
        cout << "Press any key to continue" << endl;
        char temp;
        system("stty raw");
        cin >> temp;
        system("stty cooked");
    }
    if (player.HP <= 0) {
        isGameover = true;
    }

    return health;
}

void enemies_movement() {
    int direction, y, x;
    
    for (int i = 0; i < NumOfEnemies; i++) {
        direction = rand() % 4 + 1;
        y = enemy[i].y;
        x = enemy[i].x;

        switch(direction) {
            case 1:
                // Move up
                if (y - 1 >= 0) {
                    if ((stage[y - 1][x] == '.') || (stage[y - 1][x] == 'P')) {
                        stage[y][x] = '.';
                        stage[y - 1][x] = 'm';
                        enemy[i].y--;
                    }
                }
                break;
            case 2:
                // Move left
                if (x - 1 >= 0) {
                    if ((stage[y][x - 1] == '.') || (stage[y][x - 1] == 'P')) {
                        stage[y][x] = '.';
                        stage[y][x - 1] = 'm';
                        enemy[i].x--;
                    }
                }
                break;
            case 3:
                // Move down
                if (y + 1 >= 0) {
                    if ((stage[y + 1][x] == '.') || (stage[y + 1][x] == 'P')) {
                        stage[y][x] = '.';
                        stage[y + 1][x] = 'm';
                        enemy[i].y++;
                    }
                }
                break;
            case 4:
                // Move right
                if (x + 1 >= 0) {
                    if ((stage[y][x + 1] == '.') || (stage[y][x + 1] == 'P')) {
                        stage[y][x] = '.';
                        stage[y][x + 1] = 'm';
                        enemy[i].x++;
                    }
                }
                break;
        }
    }

    // On collision, enter battle stage
    int enemyHP;
    for (int i = 0; i < NumOfEnemies; i++) {
        if ((player.y == enemy[i].y) && (player.x == enemy[i].x)) {
            enemyHP = battle(enemy[i].health);
            if (player.HP <= 0) {
                gameover();
                break;
            }
            else if ((enemyHP <= 0) && (player.HP >= 0)) {
                destroy_enemy(i);
            }
        }
    }
}

void move(int difficulty, int height, int width) {
    char input;

    system("stty raw");
    // Set the Linux system to RAW mode, allowing for raw inputs (i.e. read the input without needing to press ENTER)
    cin >> input;
    system("stty cooked");
    // Revert the Linux system back to normal mode

    switch(input) {
        case 'w':
            // Move up
            if ((player.y - 1) >= 0) {
                if (stage[player.y - 1][player.x] != 'x') {
                    if (stage[player.y - 1][player.x] == 'T') {
                        player.treasure++;
                    }
                    else if (stage[player.y - 1][player.x] == 'W') {
                        player.weapon++;
                    }
                    stage[player.y][player.x] = '.';
                    stage[player.y - 1][player.x] = 'P';
                    player.y--;
                }
            }
            break;
        case 'a':
            // Move left
            if ((player.x - 1) >= 0) {
                if (stage[player.y][player.x - 1] != 'x') {
                    if (stage[player.y][player.x - 1] == 'T') {
                        player.treasure++;
                    }
                    else if (stage[player.y][player.x - 1] == 'W') {
                        player.weapon++;
                    }
                    stage[player.y][player.x] = '.';
                    stage[player.y][player.x - 1] = 'P';
                    player.x--;
                }
            }
            break;
        case 's':
            // Move down
            if ((player.y + 1) <= (height - 1)) {
                if (stage[player.y + 1][player.x] != 'x') {
                    if (stage[player.y + 1][player.x] == 'T') {
                        player.treasure++;
                    }
                    else if (stage[player.y + 1][player.x] == 'W') {
                        player.weapon++;
                    }
                    stage[player.y][player.x] = '.';
                    stage[player.y + 1][player.x] = 'P';
                    player.y++;
                }
            }
            break;
        case 'd':
            // Move right
            if ((player.x + 1) <= (width - 1)) {
                if (stage[player.y][player.x + 1] != 'x') {
                    if (stage[player.y][player.x + 1] == 'T') {
                        player.treasure++;
                    }
                    else if (stage[player.y][player.x + 1] == 'W') {
                        player.weapon++;
                    }
                    stage[player.y][player.x] = '.';
                    stage[player.y][player.x + 1] = 'P';
                    player.x++;
                }
            }
            break;
        case 'q':
            // Quit
            refresh();
            save(difficulty, height, width);
            isGameover = true;
            break;
    }

    // On collision, enter battle stage
    int enemyHP;
    for (int i = 0; i < NumOfEnemies; i++) {
        if ((player.y == enemy[i].y) && (player.x == enemy[i].x)) {
            enemyHP = battle(enemy[i].health);
            if (player.HP <= 0) {
                gameover();
                break;
            }
            else if ((enemyHP <= 0) && (player.HP >= 0)) {
                destroy_enemy(i);
            }
        }
    }
}

bool isGoal(int height, int width) {
    if ((player.y == (height - 1)) && (player.x == (width - 1))) {
        return true;
    }
    else {
        return false;
    }
}

void boss_stage() {
    isBossStage = true; 
    
    refresh();
    cout << "BOSS STAGE!!!" << endl;
    cout << endl << "Are you READY?" << endl;
    cout << "Press any key to continue" << endl;
    char temp;
    system("stty raw");
    cin >> temp;
    system("stty cooked");

    int health = 10;
    health = battle(health);

    if (player.HP <= 0) {
        gameover();
    }
    else if ((health <= 0) && (player.HP >= 0)) {
        victory();
    }
}

void save(int difficulty, int height, int width) {
    ofstream output;
    output.open("savelog.txt");

    output << difficulty << endl;

    output << player.HP << endl;
    output << player.treasure << endl;
    output << player.weapon << endl;
    output << player.y << endl;
    output << player.x << endl;
    output << player.kills << endl;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            output << stage[i][j] << " ";
        }
        output << endl;
    }

    for (int i = 0; i < NumOfEnemies; i++) {
        output << enemy[i].health << endl;
        output << enemy[i].y << endl;
        output << enemy[i].x << endl;
    }

    cout << "Progress saved as 'savelog.txt'" << endl;
    cout << "Press any key to exit";
    char temp;
    system("stty raw");
    cin >> temp;
    system("stty cooked");

    output.close();
}

void load(int &difficulty,int &height, int &width) {
    ifstream input;
    input.open("savelog.txt");

    input >> difficulty;
    switch(difficulty) {
        case 1:
            width = 20;
            height = 10;
            NumOfEnemies = 3;
            break;
        case 2:
            width = 30;
            height = 15;
            NumOfEnemies = 6;
            break;
        case 3:
            width = 40;
            height = 20;
            NumOfEnemies = 9;
            break;
    }

    input >> player.HP;
    input >> player.treasure;
    input >> player.weapon;
    input >> player.y;
    input >> player.x;
    input >> player.kills;
    
    map.clear();
    // As the map (dynamic memory) is not need if we load existing progress instead of generating a new map,
    // the map is cleared in order to save computer resources (dynamic memory management)
    stage.clear();
    stage.resize(height, vector<char>(width));
    // The "stage" dynamic memory is resized (reduced) from the origianlly initiaitsed maximum size in order to free computer resources

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            input >> stage[i][j];
        }
    }

    for (int i = 0; i < NumOfEnemies; i++) {
        input >> enemy[i].health;
        input >> enemy[i].y;
        input >> enemy[i].x;
    }

    input.close();
}

bool startgame() {
    int input = 0;
    bool isNewGame = false;

    cout << "Welcome!" << endl;
    cout << "1. New game" << endl;
    cout << "2. Load game" << endl;
    system("stty raw");
    cin >> input;
    system("stty cooked");

    if (input == 1) {
        isNewGame = true;
    }
    else if (input == 2) {
        isNewGame = false;
    }

    return isNewGame;
}



// ********** Main Program **********

int main() {
    bool isNewGame = startgame();
    int difficulty = 0, height = 0, width = 0;
    if (isNewGame) {
        refresh();
        difficulty = select_difficulty();
        switch(difficulty) {
            case 1:
                width = 20;
                height = 10;
                break;
            case 2:
                width = 30;
                height = 15;
                break;
            case 3:
                width = 40;
                height = 20;
                break;
        }
        
        do {
            generate_map(height, width);
        }
        while (not isMapValid(height, width));

        generate_game_items(height, width, difficulty);
        generate_stage(height, width);
        generate_enemies(height, width, difficulty);
    }
    else if (not isNewGame) {
        refresh();
        load(difficulty, height, width);    // This is pass by reference
    }

    showstage(height, width);

    while (not isGameover) {
        while (not isGoal(height, width)) {
            move(difficulty, height, width);
            // Enemies will move after the player's turn ended
            enemies_movement();
            if (isGameover) {
                break;
            }
            showstage(height, width);
        }
        if (isGameover) {
            break;
        }
        else if (not isGameover) {
            boss_stage();
        }
    }

    return 0;
}
