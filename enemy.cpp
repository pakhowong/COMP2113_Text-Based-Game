#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


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


void destroy_enemy(int enemyID) {
    // Move the enemies out of the map (so they wont "move" anymore)
    enemy[enemyID].y = -10;
    enemy[enemyID].x = -10;
    player.kills++;
    // Remove the "m" from the map
    stage[player.y][player.x] = 'P';
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
