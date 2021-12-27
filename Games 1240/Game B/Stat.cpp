#include "Stat.h"

/**
 * Implementation of Stat class functions
 */

Stat::Stat(int t, int sqClicked, int diff) {
    time = t;
    squaresClicked = sqClicked;
    difficulty = diff;
}

int Stat::getTime() {
    return time;
}

void Stat::setTime(int t) {
    time = t;
}

int Stat::getSquaresClicked() {
    return squaresClicked;
}

void Stat::setSquaresClicked(int sqClicked) {
    squaresClicked = sqClicked;
}

int Stat::getDifficulty() {
    return difficulty;
}

void Stat::setDifficulty(int diff) {
    difficulty = diff;
}
