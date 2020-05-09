#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


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
