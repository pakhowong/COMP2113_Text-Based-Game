#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

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
