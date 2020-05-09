#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void refresh() {
    // Linux ONLY
    // To clear everything on the screen
    printf("\033c");
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

