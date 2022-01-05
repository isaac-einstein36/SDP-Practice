#include "includeFile.h"

#define CHAR_HEIGHT 17
#define CHAR_WIDTH 12

// Shows the menu
/**
 * @brief Displays the menu including animated road and car. Has user pick what option they want to do (play, rules, etc.)
 * 
 * @return const char* userChoice which is what the user picked to do (play, rules, etc.)
 */
const char *runMenu()
{

        // Clear screen
        initializeMenu();

        // Draw road with car going across while title is drawn
        menuGraphics();

        // Pause
        usleep(carSpeed * 1E6);

        // Display Credits
        credits();

        // Show the menu options
        const char *userChoice = showMenuOptions();

        return userChoice;
}

// Initializes the menu to LIGHTSALMON
void initializeMenu()
{

        // Clear the screen and set font/background colors
        LCD.SetBackgroundColor(LIGHTSALMON);
        LCD.SetFontColor(LIGHTGRAY);
        LCD.Clear();
        LCD.Update();
}

// Function to draw animated road, and then calls function to draw the car moving across road while title is drawn
void menuGraphics()
{

        // Draw road with a moving car
        int startRoad = 25;
        ROAD menuRoad(startRoad, true);

        // menuRoad.animated = true;
        menuRoad.drawRoad();

        usleep(carSpeed * 1E6);

        VEHICLE car("car2", startRoad);

        car.setDelay(carSpeed);

        carWithTitle(car);
}

// Draws a moving car along with "CROSSY ROAD"
void carWithTitle(VEHICLE car)
{

        string title = "CROSSY-ROAD";

        for (int i = 0; i < title.length(); i++)
        {

                car.drawVehicle();

                // Draw the car and each letter of title
                LCD.SetFontColor(GRAY);
                LCD.WriteAt(title.at(i), XDIM / (title.length() * 2) * i + (XDIM / 4), 100);

                if (car.carPosX < 250)
                {
                        // LCD.WriteAt(i, XDIM / (title.length() * 2) * i + (XDIM / 4), 200);
                        car.moveVehicle();
                }
                else
                {
                        LCD.Update();
                }
        }
}

/**
 * Function to show the menu options (i.e. play game, stats, instructions, etc.)
*/
const char *showMenuOptions()
{
        LCD.SetFontColor(GRAY);
        int numBoxes = 4, boxLength = XDIM / (numBoxes + 1), boxHeight = 30;
        int yBox = 150;
        int xBoxes[numBoxes];

        // B/C letters are 12 pixels wide and boxes are 70, strings can only be 5 char or less (70/12 = 5.8)
        const char *options[4] = {"Play", "Stats", "Rules", "Quit"};

        // Draw menu options
        for (int i = 0; i < numBoxes; i++)
        {
                int xBox = XDIM / (numBoxes)*i + 5;
                LCD.DrawRectangle(xBox, yBox, boxLength, boxHeight);
                xBoxes[i] = xBox;

                // Fill in text for boxes
                // Convert to string to find length
                string str(options[i]);

                int len = str.length();

                int xPos = (((boxLength - (CHAR_WIDTH * len)) / 2) + xBoxes[i]);
                int yPos = ((boxHeight - CHAR_HEIGHT) / 2) + yBox;

                // Write the text centered in the box
                LCD.WriteAt(options[i], xPos, yPos);
        }

        // Wait for touch
        float x, y;
        while (!LCD.Touch(&x, &y))
        {
        }

        // Wait until the touch releases
        while (LCD.Touch(&x, &y))
        {
        }

        // Based on where the touch was, select the corresponding function
        for (int i = 0; i < 4; i++)
        {
                if (x >= xBoxes[i] && x <= xBoxes[i] + boxLength)
                {
                        // LCD.WriteAt(options[i], 0, 225);
                        // LCD.Update();
                        return options[i];
                }
        }

        return "";
}

// Function to display credits
void credits()
{

        char credits[] = "By : Isaac Einstein";

        // LCD.WriteAt(credits, (XDIM - sizeof(credits)) / 2, 200);
        int length = sizeof(credits) / sizeof(*credits) - 1;

        int xPos = (XDIM - CHAR_WIDTH * length) / 2;

        LCD.WriteAt(credits, xPos, YDIM - CHAR_HEIGHT);

        LCD.Update();
}