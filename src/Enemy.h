//
// Created by Caio on 19/08/2023.
//

#ifndef GAME01_ENEMY_H
#define GAME01_ENEMY_H

#include "Player.h"

class Enemy : public Player {
public:
    Enemy(int initialX, int initialY, PlayerKeys keys, AsciiChar charToRender) : Player(initialX, initialY, keys, charToRender) {

    }

    Enemy() {}
};

#endif //GAME01_ENEMY_H
