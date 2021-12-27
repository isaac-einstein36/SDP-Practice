#include "FEHLCD.h"
#include "FEHImages.h"
#include <string>
#include <unistd.h>

// Define functions
void displayMenu();
void drawBoard();

// Main function
int main()
{

    LCD.Clear();
    LCD.SetBackgroundColor(BLUE);
    LCD.SetFontColor(LIGHTGRAY);
    LCD.Write("HELLO WORLD");
    LCD.Update();

    // Pause for click
    int x, y;
while (!LCD.Touch(&x,&y))
{
}


    while (1)
    {
        LCD.Update();
        // Never end
    }
    return 0;
}
