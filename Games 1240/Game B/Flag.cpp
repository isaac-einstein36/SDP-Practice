#include "Flag.h"
#include "FEHLCD.h"
/**
 * Implementation of Flag class functions
 */
Flag::Flag(int x, int y) {
    xCoord = x;
    yCoord = y;
}

int Flag::getXCoord() {
    return xCoord;
}

int Flag::getYCoord() {
    return yCoord;
}

void Flag::drawFlag() {
    /**
     * Draw the top part of the flag
     * A red filled rectangles with a 
     * black border rectangle
     */
    LCD.SetDrawColor(LCD.Red);
    LCD.FillRectangle(xCoord + 5, yCoord + 3, 10, 7);
    LCD.SetDrawColor(LCD.Black);
    LCD.DrawRectangle(xCoord + 5, yCoord + 3, 10, 7);

    /**
     * Draw the "pole" of the flag
     * Use a verticle line
     */
    LCD.SetDrawColor(LCD.Black);
    LCD.DrawVerticalLine(xCoord + 14, yCoord + 10, yCoord + 18);
}