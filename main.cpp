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
