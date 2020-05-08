#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

const int Max_map_height = 30, Max_map_width = 60;
const int Max_enemies = 9;

// Game elements
vector < vector < int > > map (Max_map_height, vector < int > (Max_map_width, 0));  // Initialise the 2-D array of map with the maximum map size allowed
vector < vector < char > > stage (Max_map_height, vector < char > (Max_map_width, 0));

int NumOfEnemies;
bool isGameover = false;

struct players {
    int y = 0, x = 0;
    int treasure = 0, weapon = 0;
    int HP = 10;
} player;

struct enemies {
    int health = 5; // Enemies' HP
    int y, x;   // Enemies' y- and x-coordinates
} enemy[Max_enemies];

void refresh() {
    // Linux ONLY
    // To clear everything on the screen
    printf("\033c");
}

int select_difficulty() {
    int difficulty = 0;
    // Allow user to choose various difficulties (size of the map)
    while ((difficulty < 1) || (difficulty > 3)) {
        cout << "Please choose the levels of difficulty (1, 2 or 3):" << endl;
        cin >> difficulty;
    }
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

    cout << "###############" << endl;
    cout << "# " << "Treasure: " << player.treasure << " #" << endl;
    cout << "# " << "Weapon:   " << player.weapon << " #" << endl;
    cout << "###############" << endl << endl;

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
    cout << "VICTORY" << endl;
    cout << endl << "You have collected " << player.treasure << " treasures!" << endl;
}

void showbattlestage(int health) {
    refresh();
    cout << "###############" << endl;
    cout << "# " << "1: Paper   " << " #" << endl;
    cout << "# " << "2: Scissors" << " #" << endl;
    cout << "# " << "3: Stone   " << " #" << endl;
    cout << "###############" << endl << endl;

    
    cout << "################" << endl;
    cout << " Enemy HP: " << health << endl;
    cout << " Your HP:  " << player.HP << endl;
    cout << "################" << endl << endl;
}

int battle(int health) {
    refresh();
    int attack = 1 + player.weapon;
    int RNG = 0;
    int input = 0;
    bool battle_end = false;

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
            cout << endl << "READY FOR NEXT ROUND? (Y/N)" << endl;
            char temp;
            cin >> temp;
            while (temp != 'y') {
                cout << "Press Y to continue" << endl;
                cin >> temp;
            }
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
            cout << endl << "READY FOR NEXT ROUND? (Y/N)" << endl;
            char temp;
            cin >> temp;
            while (temp != 'y') {
                cout << "Press Y to continue" << endl;
                cin >> temp;
            }
        }
        else if (((input == 1) && (RNG == 1)) || ((input == 2) && (RNG == 2)) || ((input == 3) && (RNG == 3))) {
            // Reset
            input = 0;
            RNG = 0;
            
            // Next Round
            cout << endl << "DRAW" << endl;
            cout << endl << "READY FOR NEXT ROUND? (Y/N)" << endl;
            char temp;
            cin >> temp;
            while (temp != 'y') {
                cout << "Press Y to continue" << endl;
                cin >> temp;
            }
        }
    }

    if (health <= 0) {
        refresh();
        cout << "CONGRATULATION!" << endl;
        cout << endl << "Enemy is defeated" << endl << endl;
        cout << "Press Y to continue" << endl;
        char temp;
        cin >> temp;
        while (temp != 'y') {
            cout << "Press Y to continue" << endl;
            cin >> temp;
        }
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

void move(int height, int width) {
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
    refresh();
    cout << "BOSS STAGE!!!" << endl;
    cout << endl << "READY? (Y/N)" << endl;
    char temp;
    cin >> temp;
    while (temp != 'y') {
        cout << "Press Y to continue" << endl;
        cin >> temp;
    }
    int health = 10;
    health = battle(health);

    if (player.HP <= 0) {
        gameover();
    }
    else if ((health <= 0) && (player.HP >= 0)) {
        victory();
    }
}

int main() {
    int difficulty = select_difficulty();
    int height = 0, width = 0;
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

    showstage(height, width);

    while (not isGameover) {
        while (not isGoal(height, width)) {
            move(height, width);
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
