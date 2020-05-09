#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


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


int battle(int health) {
    refresh();
    int attack = 1 + player.weapon;
    int RNG = 0;
    int input = 0;
    bool battle_end = false;
    
    while (not battle_end) {
        if (not isBossStage) {
            showbattlestage(health);
        }
        else {
            showbossbattlestage(health);
        }
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



bool isGoal(int height, int width) {
    if ((player.y == (height - 1)) && (player.x == (width - 1))) {
        return true;
    }
    else {
        return false;
    }
}
