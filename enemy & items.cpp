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


void destroy_enemy(int enemyID) {
    // Move the enemies out of the map (so they wont "move" anymore)
    enemy[enemyID].y = -10;
    enemy[enemyID].x = -10;
    player.kills++;
    // Remove the "m" from the map
    stage[player.y][player.x] = 'P';
}

