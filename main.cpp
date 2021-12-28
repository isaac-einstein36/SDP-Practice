// File for all include statements
#include "includes.h"

// Local functions
void displayMenu();
void menuGraphics();
// void moveCar();

// Declare global variables
int XDIM, YDIM;

// Functions used from other files (can be declared in source files but don't need to be)
void drawRoad(int roadStartY, int roadHeight, bool animate);
void drawCar(int carStartX, int carStartY);
void moveCar(int roadStartY);
void eraseCar(int roadStartY);

// Main function
int main()
{
    // Initialize global variables
    XDIM = 320;
    YDIM = 240;

    displayMenu();

    // Pause for click
    int x, y;
    while (!LCD.Touch(&x, &y))
    {
    }

    LCD.Clear();
    LCD.Write("GOODBYE!");

    while (1)
    {
        LCD.Update();
        // Never end
    }
    return 0;
}

/**
 * Function to show the menu options (i.e. play game, stats, instructions, etc.)
*/

void displayMenu()
{

    // Clear the screen and set font/background colors
    LCD.SetBackgroundColor(LIGHTSALMON);
    LCD.SetFontColor(LIGHTGRAY);
    LCD.Clear();
    LCD.Update();

    // Draw road with car going across
    menuGraphics();
}

void menuGraphics()
{

    // Draw road with a moving car
    int roadStartY = 50, roadHeight = 50;
    drawRoad(roadStartY, roadHeight, false);

    moveCar(roadStartY);
}
