#include "Mine.h"
#include "FEHLCD.h"

/**
 * Implementation of Mine class functions
 */
Mine::Mine(int x, int y) {
    xCoord = x;
    yCoord = y;
}

int Mine::getXCoord() {
    return xCoord;
}

int Mine::getYCoord() {
    return yCoord;
}

void Mine::drawMine() {
    /**
     * Draw black filled circle with a radius of 5
     * in the center of the square
     */
    LCD.SetDrawColor(LCD.Black);
    LCD.FillCircle(xCoord + 10, yCoord + 10, 5);

    /**
     * Draw "spikes" around the outisde
     * of the circle to resemble a mine
     */
    LCD.DrawVerticalLine(xCoord + 10, yCoord + 5, yCoord);
    LCD.DrawVerticalLine(xCoord + 10, yCoord + 15, yCoord + 18);

    LCD.DrawHorizontalLine(yCoord + 10, xCoord + 5, xCoord);
    LCD.DrawHorizontalLine(yCoord + 10, xCoord + 15, xCoord + 18);

    LCD.DrawLine(xCoord + 5, yCoord + 5, xCoord + 4, yCoord + 4);
    LCD.DrawLine(xCoord + 15, yCoord + 5, xCoord + 16, yCoord + 4);
    LCD.DrawLine(xCoord + 5, yCoord + 15, xCoord + 4, yCoord + 16);
    LCD.DrawLine(xCoord + 15, yCoord + 15, xCoord + 16, yCoord + 16);
}