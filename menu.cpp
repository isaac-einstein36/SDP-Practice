#include "includeHeaders.h"
#include "includeFiles.h"

// Shows the menu
void runMenu()
{

        // thread t1(initializeMenu);


        // Clear screen
        initializeMenu();

        // Draw road with car going across
        // menuGraphics();

        // // Write the title
        // menuTitle();

        // // Show the menu options
        // showMenuOptions();
}

void initializeMenu()
{

        // Clear the screen and set font/background colors
        LCD.SetBackgroundColor(LIGHTSALMON);
        LCD.SetFontColor(LIGHTGRAY);
        LCD.Clear();
        LCD.Update();
}

void menuGraphics()
{

        // Draw road with a moving car
        int startRoad = 25;
        ROAD menuRoad(startRoad, true);

        // menuRoad.animated = true;
        menuRoad.drawRoad();

        usleep(1 * 1E6);

        VEHICLE car("car", startRoad);

        car.setDelay(0.5);

        // Move the vehicle to the end of the road
        while (car.carPosX < 250)
        {
                car.moveVehicle();
        }

        // Erase car after it gets to the end of the road
        usleep(0.5 * 1E6);

        car.eraseVehicle();
}

/**
 * Function to show the menu options (i.e. play game, stats, instructions, etc.)
*/

void showMenuOptions()
{
        LCD.SetFontColor(GRAY);
        int numBoxes = 4;
        for (int i = 0; i < numBoxes; i++)
        {
                LCD.DrawRectangle(XDIM / (numBoxes)*i + 5, 150, 70, 25);
        }
}

void menuTitle()
{

        string title = "CROSSY ROAD";

        for (int i = 0; i < title.length(); i++)
        {
                LCD.WriteAt(title.at(i), XDIM / (title.length() * 2) * i + (XDIM / 4), 100);
                usleep(0.5 * 1E6);
                LCD.Update();
        }

        LCD.Update();
}
