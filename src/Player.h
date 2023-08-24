//
// Created by Caio on 19/08/2023.
//

#ifndef GAME01_PLAYER_H
#define GAME01_PLAYER_H

#include "enums/AsciiChar.h"
#include "../config.h"
#include "LabirinthGenetator.h"

struct PlayerKeys {
    char moveUp;
    char moveDown;
    char moveRight;
    char moveLeft;
};

class Player {

private:
    PlayerKeys keys {};
    AsciiChar charToRender;

    static bool isValidToMove(int row, int column) {
        if (row < 0 || row >= MAP_SIZE) return false;
        if (column < 0 || column >= MAP_SIZE) return false;

        int value = MAP[row][column];

        if (value == 1) return false;

        return true;
    }

public:
    int x;
    int y;

    Player(int initialX, int initialY, PlayerKeys keys, AsciiChar charToRender) {
        this->x = initialX;
        this->y = initialY;
        this->keys = keys;
        this->charToRender = charToRender;
    }

    Player() {}

    void tick(char key) {
        if (key == keys.moveUp && isValidToMove(y - 1, x)) {
            this->y--;
        }

        if (key == keys.moveDown && isValidToMove(y + 1, x)) {
            this->y++;
        }

        if (key == keys.moveRight && isValidToMove(y, x + 1)) {
            this->x++;
        }

        if (key == keys.moveLeft && isValidToMove(y, x - 1)) {
            this->x--;
        }
    }

    char render() {
        return char(charToRender);
    }
};

#endif //GAME01_PLAYER_H
