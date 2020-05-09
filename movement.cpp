#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

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

void player_movement(int difficulty, int height, int width) {
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
