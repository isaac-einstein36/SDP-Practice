// File for all include statements
#include "includeFile.h"

// Declare global variables
int XDIM, YDIM;
float carSpeed;

// Main function
int main()
{
    // Initialize global variables
    XDIM = 320;
    YDIM = 240;
    carSpeed = 0.4;

    LCD.ClearBuffer();
    LCD.Clear();

    // Run the menu function to show the menu and have user click which option to do (play, rules, etc.)
    const char *userChoice = runMenu();

    LCD.Clear();
    LCD.Write(userChoice);

    // Pause for click
    float a, b;
    while (!LCD.Touch(&a, &b))
    {
    }

    LCD.Write("GOODBYE!");

    // Never end
    while (1)
    {
        LCD.Update();
    }
    return 0;
}
