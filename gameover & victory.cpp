#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


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









