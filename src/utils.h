//
// Created by Caio on 20/08/2023.
//

#ifndef GAME01_UTILS_H
#define GAME01_UTILS_H

#include <iostream>

using namespace std;

const int barWidth = 5;

string getProgressBar(int currentProgress, int maxProgress) {
    int percent = (currentProgress * 100) / maxProgress;

    int numChars = (barWidth * percent) / 100;
    string bar;

    bar.append("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < numChars) {
            bar.append("#");
        } else {
            bar.append(" ");
        }
    }

    bar.append("] ");
    bar.append(to_string(percent));
    bar.append("%");

    return bar;
}

#endif //GAME01_UTILS_H
