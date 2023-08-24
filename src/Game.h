//
// Created by Caio on 19/08/2023.
//

#ifndef GAME01_GAME_H
#define GAME01_GAME_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include "Player.h"
#include "../config.h"
#include "LabirinthGenetator.h"
#include "utils.h"
#include "Enemy.h"

using namespace std;

class Game {

private:
    Player player;
    Enemy enemy;

    COORD coord {};
    bool running = true;
    int columns, rows;

    void tick() {
        char pressedKey;

        if (_kbhit()) {
            pressedKey = getch();
        }

        if (pressedKey == 'q') {
            running = false;
            return;
        }

        player.tick(pressedKey);
        enemy.tick(pressedKey);
    }

    void render() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        int currentHudRow = 0;
        for (int row = 0; row < MAP_SIZE; ++row) {
            for (int column = 0; column < MAP_SIZE; ++column) {
                if (row == player.y && column == player.x) {
                    cout << " " << player.render() << " ";
                    continue;
                }

                if (row == enemy.y && column == enemy.x) {
                    cout << " " << enemy.render() << " ";
                    continue;
                }

                int isWall = MAP[row][column];

                if (isWall) {
                    cout << char(AsciiChar::WALL) << char(AsciiChar::WALL) << char(AsciiChar::WALL);
                    continue;
                }

                cout << "   ";
            }

            if (row > ((MAP_SIZE - HUD_SIZE - 1) / 2) && currentHudRow < HUD_SIZE) {
                string toRender = HUD[currentHudRow];

                size_t found = toRender.find("$bar");
                if (found != std::string::npos) {
                    toRender.replace(found, 5, getProgressBar(3, 5));
                }

                cout << "         " << toRender;
                currentHudRow++;
            }
            cout << endl;
        }
    }

public:
    Game() {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
        columns = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
        rows = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);

        initGameMap();

        coord.X = 0;
        coord.Y = 0;

        PlayerKeys keys = {};
        keys.moveUp = 'w';
        keys.moveDown = 's';
        keys.moveLeft = 'a';
        keys.moveRight = 'd';

        Player newPlayer(1, 1, keys, AsciiChar::SMALL_BLOCK);

        PlayerKeys enemyKeys = {};
        enemyKeys.moveUp = 'i';
        enemyKeys.moveDown = 'k';
        enemyKeys.moveLeft = 'j';
        enemyKeys.moveRight = 'l';

        Enemy newEnemy(11, 11, enemyKeys, AsciiChar::SMALL_CIRCLE);

        this->player = newPlayer;
        this->enemy = newEnemy;
    }

    void run() {
        while(running) {
            tick();
            render();
            usleep(1000000 / 60);
        }
    }
};

#endif //GAME01_GAME_H
