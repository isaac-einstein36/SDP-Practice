// File for all include statements
#include "includeHeaders.h"
#include "includeFiles.h"

// Declare global variables
int XDIM, YDIM;

// Main function
int main()
{
    // Initialize global variables
    XDIM = 320;
    YDIM = 240;

    runMenu();

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
