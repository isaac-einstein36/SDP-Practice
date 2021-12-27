#include "Square.h"

/**
 * Implemtation of Square class functions
 */
Square::Square(int x, int y, bool m){
    xCoord = x;
    yCoord = y;
    mine = m;
    /**
     * This is unknown at the time of instantiation
     * so it's intialized to 0
     */
    value = 0;
    
    //Always false for a new square
    revealed = false;
    flagged = false;
}

int Square::getXCoord() {
    return xCoord;
}

int Square::getYCoord() {
    return yCoord;
}

bool Square::getMine() {
    return mine;
}

int Square::getValue() {
    return value;
}

void Square::setValue(int v) {
    value = v;
}

bool Square::getRevealed() {
    return revealed;
}

void Square::setRevealed(bool r) {
    revealed = r;
}

bool Square::getFlagged() {
    return flagged;
}

void Square::setFlagged(bool f) {
    flagged = f;
}

