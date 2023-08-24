//
// Created by Caio on 20/08/2023.
//

#ifndef GAME01_LABIRINTHGENETATOR_H
#define GAME01_LABIRINTHGENETATOR_H

#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAP_SIZE = 21;

vector<vector<short>> MAP(MAP_SIZE, vector<short>(MAP_SIZE, 1));

bool isValid(int x, int y) {
    return x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE && MAP[y][x] == 1;
}

void generateMaze(int x, int y) {
    static const int dx[] = { 1, 0, -1, 0 };
    static const int dy[] = { 0, 1, 0, -1 };

    int dirs[4] = { 0, 1, 2, 3 };
    shuffle(dirs, dirs + 4, std::mt19937(std::random_device()()));

    MAP[y][x] = 0;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dirs[i]] * 2;
        int ny = y + dy[dirs[i]] * 2;

        if (isValid(nx, ny)) {
            MAP[ny][nx] = 0;
            MAP[y + dy[dirs[i]]][x + dx[dirs[i]]] = 0;
            generateMaze(nx, ny);
        }
    }
}

void initGameMap() {
    srand(time(nullptr));

    int startX = 1;
    int startY = 1;

    if (startX % 2 == 0) startX++;
    if (startY % 2 == 0) startY++;

    generateMaze(startX, startY);
}

#endif //GAME01_LABIRINTHGENETATOR_H
