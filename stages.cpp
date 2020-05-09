#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

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

void showbattlestage(int health) {
    refresh();

    //player & monster 
    cout << "    _O_    " << "           " << endl; 
    cout << "  /     \\  " << "           " << endl; 
    cout << " |==/=\\==| " << "           " << "   .-.    " << endl;
    cout << " |  O O  | " << "           " << "  (o o)   " << endl;
    cout << "  \\  V  /  " << "           " << "  | O \\   " << endl;
    cout << "  /`---'\\  " << "           " << "   \\   \\  " << endl;
    cout << "  O'_:_`O  " << "           " << "    `~~~' " << endl;
    cout << "   -- --   " << "           " << endl; 
    
    cout << endl << endl;
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
    refresh();

    //boss monster
    cout << "         (  )   /\\   _                 (                                            " << endl;
    cout << "      \\ |  (  \\ ( \\.(               )                      _____                    " << endl;
    cout << "    \\  \\ \\  `  `   ) \\             (  ___                 / _   \\                   " << endl;
    cout << "   (_`    \\+   . x  ( .\\            \\/   \\____-----------/ (o)   \\_                 " << endl;
    cout << "  - .-               \\+  ;          (  O                           \\____            " << endl;
    cout << "                            )        \\_____________  `              \\  /            " << endl;
    cout << "  (__                +- .( -'.- <. - _  VVVVVVV VV V\\                 \\/            " << endl;
    cout << "  (_____            ._._: <_ - <- _  (--  _AAAAAAA__A_/                  |          " << endl;
    cout << "    .    /./.+-  . .- /  +--  - .     \\______________//_              \\_______      " << endl;
    cout << "    (__ ' /x  / x _/ (                                  \\___'          \\     /      " << endl;
    cout << "   , x / ( '  . / .  /                                      |           \\   /       " << endl;
    cout << "      /  /  _/ /    +                                      /              \\/        " << endl;
    cout << "     '  (__/                                             /                  \\       " << endl;

    cout << endl << endl;
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
