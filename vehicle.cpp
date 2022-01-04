#include "includeHeaders.h"

/**
 * @brief Draws a car from "ColoredCarFEH.pic"
 */

VEHICLE::VEHICLE(char userType[], int startHeight)
{

        carPosX = 0;
        carPosY = startHeight;
        delayTime = 100;

        strcpy(type, userType);

        strcpy(name, "ImageCreation/");
        strcat(name, type);
        strcat(name, "FEH.pic");
}

void VEHICLE::drawVehicle()
{
        FEHIMAGE pic;
        pic.Open(name);
        pic.Draw(carPosX, carPosY);
        LCD.Update();
}

void VEHICLE::eraseVehicle()
{
        // Cars are only driven on a road, so redrawing the road erases the car
        ROAD erasedRoad(carPosY);
        erasedRoad.drawRoad();
}

void VEHICLE::moveVehicle()
{

        drawVehicle();

        usleep(delayTime * 1E6);

        // Erase the previous car by drawing the road again
        eraseVehicle();

        // Draw the new car 50 pixels to the right
        carPosX += 25;
        drawVehicle();
}

void VEHICLE::setDelay(float delay)
{
        delayTime = delay;
}